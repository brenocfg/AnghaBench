#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_10__ {int pairwise_cipher_wpa; int pairwise_cipher_wpa2; int group_cipher; int length; int /*<<< orphan*/  passphrase; } ;
struct mwifiex_uap_bss_param {int key_mgmt_operation; int key_mgmt; TYPE_5__ wpa_cfg; } ;
struct mwifiex_ie_types_header {int dummy; } ;
struct TYPE_7__ {void* len; void* type; } ;
struct host_cmd_tlv_pwk_cipher {int cipher; void* proto; TYPE_2__ header; } ;
struct TYPE_9__ {void* len; void* type; } ;
struct host_cmd_tlv_passphrase {int /*<<< orphan*/  passphrase; TYPE_4__ header; } ;
struct TYPE_8__ {void* len; void* type; } ;
struct host_cmd_tlv_gwk_cipher {int cipher; TYPE_3__ header; } ;
struct TYPE_6__ {void* len; void* type; } ;
struct host_cmd_tlv_akmp {void* key_mgmt; void* key_mgmt_operation; TYPE_1__ header; } ;

/* Variables and functions */
 int PROTOCOL_WPA ; 
 int PROTOCOL_WPA2 ; 
 int TLV_TYPE_GWK_CIPHER ; 
 int TLV_TYPE_PWK_CIPHER ; 
 int TLV_TYPE_UAP_AKMP ; 
 int TLV_TYPE_UAP_WPA_PASSPHRASE ; 
 int VALID_CIPHER_BITMAP ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mwifiex_uap_bss_wpa(u8 **tlv_buf, void *cmd_buf, u16 *param_size)
{
	struct host_cmd_tlv_pwk_cipher *pwk_cipher;
	struct host_cmd_tlv_gwk_cipher *gwk_cipher;
	struct host_cmd_tlv_passphrase *passphrase;
	struct host_cmd_tlv_akmp *tlv_akmp;
	struct mwifiex_uap_bss_param *bss_cfg = cmd_buf;
	u16 cmd_size = *param_size;
	u8 *tlv = *tlv_buf;

	tlv_akmp = (struct host_cmd_tlv_akmp *)tlv;
	tlv_akmp->header.type = cpu_to_le16(TLV_TYPE_UAP_AKMP);
	tlv_akmp->header.len = cpu_to_le16(sizeof(struct host_cmd_tlv_akmp) -
					sizeof(struct mwifiex_ie_types_header));
	tlv_akmp->key_mgmt_operation = cpu_to_le16(bss_cfg->key_mgmt_operation);
	tlv_akmp->key_mgmt = cpu_to_le16(bss_cfg->key_mgmt);
	cmd_size += sizeof(struct host_cmd_tlv_akmp);
	tlv += sizeof(struct host_cmd_tlv_akmp);

	if (bss_cfg->wpa_cfg.pairwise_cipher_wpa & VALID_CIPHER_BITMAP) {
		pwk_cipher = (struct host_cmd_tlv_pwk_cipher *)tlv;
		pwk_cipher->header.type = cpu_to_le16(TLV_TYPE_PWK_CIPHER);
		pwk_cipher->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_pwk_cipher) -
				    sizeof(struct mwifiex_ie_types_header));
		pwk_cipher->proto = cpu_to_le16(PROTOCOL_WPA);
		pwk_cipher->cipher = bss_cfg->wpa_cfg.pairwise_cipher_wpa;
		cmd_size += sizeof(struct host_cmd_tlv_pwk_cipher);
		tlv += sizeof(struct host_cmd_tlv_pwk_cipher);
	}

	if (bss_cfg->wpa_cfg.pairwise_cipher_wpa2 & VALID_CIPHER_BITMAP) {
		pwk_cipher = (struct host_cmd_tlv_pwk_cipher *)tlv;
		pwk_cipher->header.type = cpu_to_le16(TLV_TYPE_PWK_CIPHER);
		pwk_cipher->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_pwk_cipher) -
				    sizeof(struct mwifiex_ie_types_header));
		pwk_cipher->proto = cpu_to_le16(PROTOCOL_WPA2);
		pwk_cipher->cipher = bss_cfg->wpa_cfg.pairwise_cipher_wpa2;
		cmd_size += sizeof(struct host_cmd_tlv_pwk_cipher);
		tlv += sizeof(struct host_cmd_tlv_pwk_cipher);
	}

	if (bss_cfg->wpa_cfg.group_cipher & VALID_CIPHER_BITMAP) {
		gwk_cipher = (struct host_cmd_tlv_gwk_cipher *)tlv;
		gwk_cipher->header.type = cpu_to_le16(TLV_TYPE_GWK_CIPHER);
		gwk_cipher->header.len =
			cpu_to_le16(sizeof(struct host_cmd_tlv_gwk_cipher) -
				    sizeof(struct mwifiex_ie_types_header));
		gwk_cipher->cipher = bss_cfg->wpa_cfg.group_cipher;
		cmd_size += sizeof(struct host_cmd_tlv_gwk_cipher);
		tlv += sizeof(struct host_cmd_tlv_gwk_cipher);
	}

	if (bss_cfg->wpa_cfg.length) {
		passphrase = (struct host_cmd_tlv_passphrase *)tlv;
		passphrase->header.type =
				cpu_to_le16(TLV_TYPE_UAP_WPA_PASSPHRASE);
		passphrase->header.len = cpu_to_le16(bss_cfg->wpa_cfg.length);
		memcpy(passphrase->passphrase, bss_cfg->wpa_cfg.passphrase,
		       bss_cfg->wpa_cfg.length);
		cmd_size += sizeof(struct mwifiex_ie_types_header) +
			    bss_cfg->wpa_cfg.length;
		tlv += sizeof(struct mwifiex_ie_types_header) +
				bss_cfg->wpa_cfg.length;
	}

	*param_size = cmd_size;
	*tlv_buf = tlv;

	return;
}