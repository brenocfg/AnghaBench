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
struct mrvl_ie_ds_param_set {int /*<<< orphan*/  channel; TYPE_1__ header; } ;

/* Variables and functions */
 int TLV_TYPE_PHY_DS ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static int lbs_add_channel_tlv(u8 *tlv, u8 channel)
{
	struct mrvl_ie_ds_param_set *ds = (void *) tlv;

	/*
	 * 03 00  TLV_TYPE_PHY_DS
	 * 01 00  len
	 * 06     channel
	 */
	ds->header.type = cpu_to_le16(TLV_TYPE_PHY_DS);
	ds->header.len = cpu_to_le16(sizeof(*ds)-sizeof(ds->header));
	ds->channel = channel;
	return sizeof(*ds);
}