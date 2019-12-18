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
struct ubifs_info {int /*<<< orphan*/  ubi; } ;

/* Variables and functions */
 int EROFS ; 
 scalar_t__ dbg_is_power_cut (struct ubifs_info*) ; 
 scalar_t__ power_cut_emulated (struct ubifs_info*,int,int) ; 
 int ubi_leb_change (int /*<<< orphan*/ ,int,void const*,int) ; 

int dbg_leb_change(struct ubifs_info *c, int lnum, const void *buf,
		   int len)
{
	int err;

	if (dbg_is_power_cut(c))
		return -EROFS;
	if (power_cut_emulated(c, lnum, 1))
		return -EROFS;
	err = ubi_leb_change(c->ubi, lnum, buf, len);
	if (err)
		return err;
	if (power_cut_emulated(c, lnum, 1))
		return -EROFS;
	return 0;
}