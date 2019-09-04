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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {struct data_queue* bcn; } ;
struct queue_entry {int /*<<< orphan*/  entry_idx; int /*<<< orphan*/  flags; } ;
struct data_queue {int limit; struct queue_entry* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCN_OFFSET0 ; 
 int /*<<< orphan*/  BCN_OFFSET1 ; 
 int /*<<< orphan*/  ENTRY_BCN_ENABLED ; 
 int /*<<< orphan*/  MAC_BSSID_DW1 ; 
 int /*<<< orphan*/  MAC_BSSID_DW1_BSS_BCN_NUM ; 
 int rt2800_get_beacon_offset (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2800_update_beacons_setup(struct rt2x00_dev *rt2x00dev)
{
	struct data_queue *queue = rt2x00dev->bcn;
	struct queue_entry *entry;
	int i, bcn_num = 0;
	u64 off, reg = 0;
	u32 bssid_dw1;

	/*
	 * Setup offsets of all active beacons in BCN_OFFSET{0,1} registers.
	 */
	for (i = 0; i < queue->limit; i++) {
		entry = &queue->entries[i];
		if (!test_bit(ENTRY_BCN_ENABLED, &entry->flags))
			continue;
		off = rt2800_get_beacon_offset(rt2x00dev, entry->entry_idx);
		reg |= off << (8 * bcn_num);
		bcn_num++;
	}

	rt2800_register_write(rt2x00dev, BCN_OFFSET0, (u32) reg);
	rt2800_register_write(rt2x00dev, BCN_OFFSET1, (u32) (reg >> 32));

	/*
	 * H/W sends up to MAC_BSSID_DW1_BSS_BCN_NUM + 1 consecutive beacons.
	 */
	bssid_dw1 = rt2800_register_read(rt2x00dev, MAC_BSSID_DW1);
	rt2x00_set_field32(&bssid_dw1, MAC_BSSID_DW1_BSS_BCN_NUM,
			   bcn_num > 0 ? bcn_num - 1 : 0);
	rt2800_register_write(rt2x00dev, MAC_BSSID_DW1, bssid_dw1);
}