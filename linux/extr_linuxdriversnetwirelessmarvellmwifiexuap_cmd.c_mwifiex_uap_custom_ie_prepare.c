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
typedef  int /*<<< orphan*/  u16 ;
struct mwifiex_ie_types_header {scalar_t__ len; int /*<<< orphan*/  type; } ;
struct mwifiex_ie_list {scalar_t__ len; int /*<<< orphan*/  ie_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLV_TYPE_MGMT_IE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mwifiex_uap_custom_ie_prepare(u8 *tlv, void *cmd_buf, u16 *ie_size)
{
	struct mwifiex_ie_list *ap_ie = cmd_buf;
	struct mwifiex_ie_types_header *tlv_ie = (void *)tlv;

	if (!ap_ie || !ap_ie->len)
		return -1;

	*ie_size += le16_to_cpu(ap_ie->len) +
			sizeof(struct mwifiex_ie_types_header);

	tlv_ie->type = cpu_to_le16(TLV_TYPE_MGMT_IE);
	tlv_ie->len = ap_ie->len;
	tlv += sizeof(struct mwifiex_ie_types_header);

	memcpy(tlv, ap_ie->ie_list, le16_to_cpu(ap_ie->len));

	return 0;
}