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
struct skl_module_fmt {int ch_map; } ;

/* Variables and functions */

__attribute__((used)) static void skl_tplg_update_chmap(struct skl_module_fmt *fmt, int chs)
{
	int slot_map = 0xFFFFFFFF;
	int start_slot = 0;
	int i;

	for (i = 0; i < chs; i++) {
		/*
		 * For 2 channels with starting slot as 0, slot map will
		 * look like 0xFFFFFF10.
		 */
		slot_map &= (~(0xF << (4 * i)) | (start_slot << (4 * i)));
		start_slot++;
	}
	fmt->ch_map = slot_map;
}