#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  const u8 ;
struct crypto_shash {int dummy; } ;
struct TYPE_5__ {struct crypto_shash* tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int CMAC_MSG_MAX ; 
 int EFBIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,struct crypto_shash*) ; 
 int /*<<< orphan*/  SMP_DBG (char*,size_t,...) ; 
 int crypto_shash_digest (TYPE_1__*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*) ; 
 int crypto_shash_setkey (struct crypto_shash*,int /*<<< orphan*/  const*,int) ; 
 TYPE_1__* desc ; 
 int /*<<< orphan*/  shash_desc_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  swap_buf (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int aes_cmac(struct crypto_shash *tfm, const u8 k[16], const u8 *m,
		    size_t len, u8 mac[16])
{
	uint8_t tmp[16], mac_msb[16], msg_msb[CMAC_MSG_MAX];
	SHASH_DESC_ON_STACK(desc, tfm);
	int err;

	if (len > CMAC_MSG_MAX)
		return -EFBIG;

	if (!tfm) {
		BT_ERR("tfm %p", tfm);
		return -EINVAL;
	}

	desc->tfm = tfm;

	/* Swap key and message from LSB to MSB */
	swap_buf(k, tmp, 16);
	swap_buf(m, msg_msb, len);

	SMP_DBG("msg (len %zu) %*phN", len, (int) len, m);
	SMP_DBG("key %16phN", k);

	err = crypto_shash_setkey(tfm, tmp, 16);
	if (err) {
		BT_ERR("cipher setkey failed: %d", err);
		return err;
	}

	err = crypto_shash_digest(desc, msg_msb, len, mac_msb);
	shash_desc_zero(desc);
	if (err) {
		BT_ERR("Hash computation error %d", err);
		return err;
	}

	swap_buf(mac_msb, mac, 16);

	SMP_DBG("mac %16phN", mac);

	return 0;
}