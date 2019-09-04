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
typedef  int u8 ;
struct fb_info {struct aafb_par* par; } ;
struct aafb_par {int /*<<< orphan*/  bt455; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt455_write_cmap_entry (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int aafb_blank(int blank, struct fb_info *info)
{
	struct aafb_par *par = info->par;
	u8 val = blank ? 0x00 : 0x0f;

	bt455_write_cmap_entry(par->bt455, 1, val);
	return 0;
}