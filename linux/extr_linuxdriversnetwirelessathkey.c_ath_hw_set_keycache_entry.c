#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ath_keyval {int kv_type; scalar_t__ kv_len; scalar_t__ kv_mic; scalar_t__ kv_txmic; scalar_t__ kv_val; } ;
struct ath_common {scalar_t__ keymax; int crypt_caps; void* ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANY ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY0 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY1 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY2 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY3 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY4 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_MAC0 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_MAC1 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_TYPE (scalar_t__) ; 
 int AR_KEYTABLE_TYPE_104 ; 
 int AR_KEYTABLE_TYPE_128 ; 
 int AR_KEYTABLE_TYPE_40 ; 
 int AR_KEYTABLE_TYPE_AES ; 
 int AR_KEYTABLE_TYPE_CCM ; 
 int AR_KEYTABLE_TYPE_CLR ; 
 int AR_KEYTABLE_TYPE_TKIP ; 
#define  ATH_CIPHER_AES_CCM 132 
#define  ATH_CIPHER_AES_OCB 131 
#define  ATH_CIPHER_CLR 130 
#define  ATH_CIPHER_TKIP 129 
#define  ATH_CIPHER_WEP 128 
 int ATH_CRYPT_CAP_CIPHER_AESCCM ; 
 int ATH_CRYPT_CAP_MIC_COMBINED ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (void*) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (void*) ; 
 int /*<<< orphan*/  REG_WRITE (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ WLAN_KEY_LEN_WEP104 ; 
 scalar_t__ WLAN_KEY_LEN_WEP40 ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ath_hw_keysetmac (struct ath_common*,scalar_t__,int /*<<< orphan*/  const*) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int get_unaligned_le32 (scalar_t__) ; 

__attribute__((used)) static bool ath_hw_set_keycache_entry(struct ath_common *common, u16 entry,
				      const struct ath_keyval *k,
				      const u8 *mac)
{
	void *ah = common->ah;
	u32 key0, key1, key2, key3, key4;
	u32 keyType;

	if (entry >= common->keymax) {
		ath_err(common, "set-entry: keycache entry %u out of range\n",
			entry);
		return false;
	}

	switch (k->kv_type) {
	case ATH_CIPHER_AES_OCB:
		keyType = AR_KEYTABLE_TYPE_AES;
		break;
	case ATH_CIPHER_AES_CCM:
		if (!(common->crypt_caps & ATH_CRYPT_CAP_CIPHER_AESCCM)) {
			ath_dbg(common, ANY,
				"AES-CCM not supported by this mac rev\n");
			return false;
		}
		keyType = AR_KEYTABLE_TYPE_CCM;
		break;
	case ATH_CIPHER_TKIP:
		keyType = AR_KEYTABLE_TYPE_TKIP;
		if (entry + 64 >= common->keymax) {
			ath_dbg(common, ANY,
				"entry %u inappropriate for TKIP\n", entry);
			return false;
		}
		break;
	case ATH_CIPHER_WEP:
		if (k->kv_len < WLAN_KEY_LEN_WEP40) {
			ath_dbg(common, ANY, "WEP key length %u too small\n",
				k->kv_len);
			return false;
		}
		if (k->kv_len <= WLAN_KEY_LEN_WEP40)
			keyType = AR_KEYTABLE_TYPE_40;
		else if (k->kv_len <= WLAN_KEY_LEN_WEP104)
			keyType = AR_KEYTABLE_TYPE_104;
		else
			keyType = AR_KEYTABLE_TYPE_128;
		break;
	case ATH_CIPHER_CLR:
		keyType = AR_KEYTABLE_TYPE_CLR;
		break;
	default:
		ath_err(common, "cipher %u not supported\n", k->kv_type);
		return false;
	}

	key0 = get_unaligned_le32(k->kv_val + 0);
	key1 = get_unaligned_le16(k->kv_val + 4);
	key2 = get_unaligned_le32(k->kv_val + 6);
	key3 = get_unaligned_le16(k->kv_val + 10);
	key4 = get_unaligned_le32(k->kv_val + 12);
	if (k->kv_len <= WLAN_KEY_LEN_WEP104)
		key4 &= 0xff;

	/*
	 * Note: Key cache registers access special memory area that requires
	 * two 32-bit writes to actually update the values in the internal
	 * memory. Consequently, the exact order and pairs used here must be
	 * maintained.
	 */

	if (keyType == AR_KEYTABLE_TYPE_TKIP) {
		u16 micentry = entry + 64;

		/*
		 * Write inverted key[47:0] first to avoid Michael MIC errors
		 * on frames that could be sent or received at the same time.
		 * The correct key will be written in the end once everything
		 * else is ready.
		 */
		REG_WRITE(ah, AR_KEYTABLE_KEY0(entry), ~key0);
		REG_WRITE(ah, AR_KEYTABLE_KEY1(entry), ~key1);

		/* Write key[95:48] */
		REG_WRITE(ah, AR_KEYTABLE_KEY2(entry), key2);
		REG_WRITE(ah, AR_KEYTABLE_KEY3(entry), key3);

		/* Write key[127:96] and key type */
		REG_WRITE(ah, AR_KEYTABLE_KEY4(entry), key4);
		REG_WRITE(ah, AR_KEYTABLE_TYPE(entry), keyType);

		/* Write MAC address for the entry */
		(void) ath_hw_keysetmac(common, entry, mac);

		if (common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED) {
			/*
			 * TKIP uses two key cache entries:
			 * Michael MIC TX/RX keys in the same key cache entry
			 * (idx = main index + 64):
			 * key0 [31:0] = RX key [31:0]
			 * key1 [15:0] = TX key [31:16]
			 * key1 [31:16] = reserved
			 * key2 [31:0] = RX key [63:32]
			 * key3 [15:0] = TX key [15:0]
			 * key3 [31:16] = reserved
			 * key4 [31:0] = TX key [63:32]
			 */
			u32 mic0, mic1, mic2, mic3, mic4;

			mic0 = get_unaligned_le32(k->kv_mic + 0);
			mic2 = get_unaligned_le32(k->kv_mic + 4);
			mic1 = get_unaligned_le16(k->kv_txmic + 2) & 0xffff;
			mic3 = get_unaligned_le16(k->kv_txmic + 0) & 0xffff;
			mic4 = get_unaligned_le32(k->kv_txmic + 4);

			ENABLE_REGWRITE_BUFFER(ah);

			/* Write RX[31:0] and TX[31:16] */
			REG_WRITE(ah, AR_KEYTABLE_KEY0(micentry), mic0);
			REG_WRITE(ah, AR_KEYTABLE_KEY1(micentry), mic1);

			/* Write RX[63:32] and TX[15:0] */
			REG_WRITE(ah, AR_KEYTABLE_KEY2(micentry), mic2);
			REG_WRITE(ah, AR_KEYTABLE_KEY3(micentry), mic3);

			/* Write TX[63:32] and keyType(reserved) */
			REG_WRITE(ah, AR_KEYTABLE_KEY4(micentry), mic4);
			REG_WRITE(ah, AR_KEYTABLE_TYPE(micentry),
				  AR_KEYTABLE_TYPE_CLR);

			REGWRITE_BUFFER_FLUSH(ah);

		} else {
			/*
			 * TKIP uses four key cache entries (two for group
			 * keys):
			 * Michael MIC TX/RX keys are in different key cache
			 * entries (idx = main index + 64 for TX and
			 * main index + 32 + 96 for RX):
			 * key0 [31:0] = TX/RX MIC key [31:0]
			 * key1 [31:0] = reserved
			 * key2 [31:0] = TX/RX MIC key [63:32]
			 * key3 [31:0] = reserved
			 * key4 [31:0] = reserved
			 *
			 * Upper layer code will call this function separately
			 * for TX and RX keys when these registers offsets are
			 * used.
			 */
			u32 mic0, mic2;

			mic0 = get_unaligned_le32(k->kv_mic + 0);
			mic2 = get_unaligned_le32(k->kv_mic + 4);

			ENABLE_REGWRITE_BUFFER(ah);

			/* Write MIC key[31:0] */
			REG_WRITE(ah, AR_KEYTABLE_KEY0(micentry), mic0);
			REG_WRITE(ah, AR_KEYTABLE_KEY1(micentry), 0);

			/* Write MIC key[63:32] */
			REG_WRITE(ah, AR_KEYTABLE_KEY2(micentry), mic2);
			REG_WRITE(ah, AR_KEYTABLE_KEY3(micentry), 0);

			/* Write TX[63:32] and keyType(reserved) */
			REG_WRITE(ah, AR_KEYTABLE_KEY4(micentry), 0);
			REG_WRITE(ah, AR_KEYTABLE_TYPE(micentry),
				  AR_KEYTABLE_TYPE_CLR);

			REGWRITE_BUFFER_FLUSH(ah);
		}

		ENABLE_REGWRITE_BUFFER(ah);

		/* MAC address registers are reserved for the MIC entry */
		REG_WRITE(ah, AR_KEYTABLE_MAC0(micentry), 0);
		REG_WRITE(ah, AR_KEYTABLE_MAC1(micentry), 0);

		/*
		 * Write the correct (un-inverted) key[47:0] last to enable
		 * TKIP now that all other registers are set with correct
		 * values.
		 */
		REG_WRITE(ah, AR_KEYTABLE_KEY0(entry), key0);
		REG_WRITE(ah, AR_KEYTABLE_KEY1(entry), key1);

		REGWRITE_BUFFER_FLUSH(ah);
	} else {
		ENABLE_REGWRITE_BUFFER(ah);

		/* Write key[47:0] */
		REG_WRITE(ah, AR_KEYTABLE_KEY0(entry), key0);
		REG_WRITE(ah, AR_KEYTABLE_KEY1(entry), key1);

		/* Write key[95:48] */
		REG_WRITE(ah, AR_KEYTABLE_KEY2(entry), key2);
		REG_WRITE(ah, AR_KEYTABLE_KEY3(entry), key3);

		/* Write key[127:96] and key type */
		REG_WRITE(ah, AR_KEYTABLE_KEY4(entry), key4);
		REG_WRITE(ah, AR_KEYTABLE_TYPE(entry), keyType);

		REGWRITE_BUFFER_FLUSH(ah);

		/* Write MAC address for the entry */
		(void) ath_hw_keysetmac(common, entry, mac);
	}

	return true;
}