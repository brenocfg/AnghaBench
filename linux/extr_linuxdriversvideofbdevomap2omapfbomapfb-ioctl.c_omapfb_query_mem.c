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
struct omapfb_mem_info {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct omapfb_info {int /*<<< orphan*/  region; } ;
struct omapfb2_mem_region {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int /*<<< orphan*/  memset (struct omapfb_mem_info*,int /*<<< orphan*/ ,int) ; 
 struct omapfb2_mem_region* omapfb_get_mem_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_put_mem_region (struct omapfb2_mem_region*) ; 

__attribute__((used)) static int omapfb_query_mem(struct fb_info *fbi, struct omapfb_mem_info *mi)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_mem_region *rg;

	rg = omapfb_get_mem_region(ofbi->region);
	memset(mi, 0, sizeof(*mi));

	mi->size = rg->size;
	mi->type = rg->type;

	omapfb_put_mem_region(rg);

	return 0;
}