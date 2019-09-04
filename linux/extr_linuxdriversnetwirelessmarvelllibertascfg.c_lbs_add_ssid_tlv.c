#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {void* len; void* type; } ;
struct mrvl_ie_ssid_param_set {int /*<<< orphan*/  ssid; TYPE_1__ header; } ;

/* Variables and functions */
 int TLV_TYPE_SSID ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int lbs_add_ssid_tlv(u8 *tlv, const u8 *ssid, int ssid_len)
{
	struct mrvl_ie_ssid_param_set *ssid_tlv = (void *)tlv;

	/*
	 * TLV-ID SSID  00 00
	 * length       06 00
	 * ssid         4d 4e 54 45 53 54
	 */
	ssid_tlv->header.type = cpu_to_le16(TLV_TYPE_SSID);
	ssid_tlv->header.len = cpu_to_le16(ssid_len);
	memcpy(ssid_tlv->ssid, ssid, ssid_len);
	return sizeof(ssid_tlv->header) + ssid_len;
}