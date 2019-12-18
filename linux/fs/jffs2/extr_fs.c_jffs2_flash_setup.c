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
struct jffs2_sb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ jffs2_cleanmarker_oob (struct jffs2_sb_info*) ; 
 scalar_t__ jffs2_dataflash (struct jffs2_sb_info*) ; 
 int jffs2_dataflash_setup (struct jffs2_sb_info*) ; 
 int jffs2_nand_flash_setup (struct jffs2_sb_info*) ; 
 scalar_t__ jffs2_nor_wbuf_flash (struct jffs2_sb_info*) ; 
 int jffs2_nor_wbuf_flash_setup (struct jffs2_sb_info*) ; 
 scalar_t__ jffs2_ubivol (struct jffs2_sb_info*) ; 
 int jffs2_ubivol_setup (struct jffs2_sb_info*) ; 

__attribute__((used)) static int jffs2_flash_setup(struct jffs2_sb_info *c) {
	int ret = 0;

	if (jffs2_cleanmarker_oob(c)) {
		/* NAND flash... do setup accordingly */
		ret = jffs2_nand_flash_setup(c);
		if (ret)
			return ret;
	}

	/* and Dataflash */
	if (jffs2_dataflash(c)) {
		ret = jffs2_dataflash_setup(c);
		if (ret)
			return ret;
	}

	/* and Intel "Sibley" flash */
	if (jffs2_nor_wbuf_flash(c)) {
		ret = jffs2_nor_wbuf_flash_setup(c);
		if (ret)
			return ret;
	}

	/* and an UBI volume */
	if (jffs2_ubivol(c)) {
		ret = jffs2_ubivol_setup(c);
		if (ret)
			return ret;
	}

	return ret;
}