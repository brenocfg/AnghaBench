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
struct vm_area_struct {int dummy; } ;
struct ffb_par {int /*<<< orphan*/  fbsize; int /*<<< orphan*/  physbase; } ;
struct fb_info {scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  ffb_mmap_map ; 
 int sbusfb_mmap_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int ffb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct ffb_par *par = (struct ffb_par *)info->par;

	return sbusfb_mmap_helper(ffb_mmap_map,
				  par->physbase, par->fbsize,
				  0, vma);
}