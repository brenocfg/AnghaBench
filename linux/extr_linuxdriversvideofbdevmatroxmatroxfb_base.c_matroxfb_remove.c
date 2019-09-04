#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vaddr; } ;
struct TYPE_8__ {int /*<<< orphan*/  base; TYPE_1__ vbase; } ;
struct TYPE_6__ {int /*<<< orphan*/  vaddr; } ;
struct TYPE_7__ {int len_maximum; int /*<<< orphan*/  base; TYPE_2__ vbase; } ;
struct matrox_fb_info {int dead; TYPE_4__ mmio; TYPE_3__ video; int /*<<< orphan*/  wc_cookie; int /*<<< orphan*/  fbcon; scalar_t__ usecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct matrox_fb_info*) ; 
 int /*<<< orphan*/  matroxfb_g450_shutdown (struct matrox_fb_info*) ; 
 int /*<<< orphan*/  matroxfb_unregister_device (struct matrox_fb_info*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_framebuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void matroxfb_remove(struct matrox_fb_info *minfo, int dummy)
{
	/* Currently we are holding big kernel lock on all dead & usecount updates.
	 * Destroy everything after all users release it. Especially do not unregister
	 * framebuffer and iounmap memory, neither fbmem nor fbcon-cfb* does not check
	 * for device unplugged when in use.
	 * In future we should point mmio.vbase & video.vbase somewhere where we can
	 * write data without causing too much damage...
	 */

	minfo->dead = 1;
	if (minfo->usecount) {
		/* destroy it later */
		return;
	}
	matroxfb_unregister_device(minfo);
	unregister_framebuffer(&minfo->fbcon);
	matroxfb_g450_shutdown(minfo);
	arch_phys_wc_del(minfo->wc_cookie);
	iounmap(minfo->mmio.vbase.vaddr);
	iounmap(minfo->video.vbase.vaddr);
	release_mem_region(minfo->video.base, minfo->video.len_maximum);
	release_mem_region(minfo->mmio.base, 16384);
	kfree(minfo);
}