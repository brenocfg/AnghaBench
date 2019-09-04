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
struct hvfb_par {int update; int fb_ready; int /*<<< orphan*/  dwork; int /*<<< orphan*/  hvfb_panic_nb; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;
struct fb_info {struct hvfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 struct fb_info* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hvfb_putmem (struct fb_info*) ; 
 int /*<<< orphan*/  panic_notifier_list ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hvfb_remove(struct hv_device *hdev)
{
	struct fb_info *info = hv_get_drvdata(hdev);
	struct hvfb_par *par = info->par;

	atomic_notifier_chain_unregister(&panic_notifier_list,
					 &par->hvfb_panic_nb);

	par->update = false;
	par->fb_ready = false;

	unregister_framebuffer(info);
	cancel_delayed_work_sync(&par->dwork);

	vmbus_close(hdev->channel);
	hv_set_drvdata(hdev, NULL);

	hvfb_putmem(info);
	framebuffer_release(info);

	return 0;
}