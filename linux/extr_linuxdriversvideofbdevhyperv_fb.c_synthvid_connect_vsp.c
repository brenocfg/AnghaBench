#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hvfb_par {scalar_t__ synthvid_version; } ;
struct hv_device {TYPE_3__* channel; } ;
struct fb_info {struct hvfb_par* par; } ;
struct TYPE_5__ {int mmio_megabytes; } ;
struct TYPE_6__ {TYPE_1__ offer; } ;
struct TYPE_7__ {TYPE_2__ offermsg; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_BUFSIZE ; 
 int /*<<< orphan*/  SYNTHVID_DEPTH_WIN7 ; 
 int /*<<< orphan*/  SYNTHVID_DEPTH_WIN8 ; 
 scalar_t__ SYNTHVID_VERSION_WIN7 ; 
 scalar_t__ SYNTHVID_VERSION_WIN8 ; 
 scalar_t__ VERSION_WIN7 ; 
 scalar_t__ VERSION_WS2008 ; 
 struct fb_info* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  screen_depth ; 
 int screen_fb_size ; 
 int synthvid_negotiate_ver (struct hv_device*,scalar_t__) ; 
 int /*<<< orphan*/  synthvid_receive ; 
 int /*<<< orphan*/  vmbus_close (TYPE_3__*) ; 
 int vmbus_open (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hv_device*) ; 
 scalar_t__ vmbus_proto_version ; 

__attribute__((used)) static int synthvid_connect_vsp(struct hv_device *hdev)
{
	struct fb_info *info = hv_get_drvdata(hdev);
	struct hvfb_par *par = info->par;
	int ret;

	ret = vmbus_open(hdev->channel, RING_BUFSIZE, RING_BUFSIZE,
			 NULL, 0, synthvid_receive, hdev);
	if (ret) {
		pr_err("Unable to open vmbus channel\n");
		return ret;
	}

	/* Negotiate the protocol version with host */
	if (vmbus_proto_version == VERSION_WS2008 ||
	    vmbus_proto_version == VERSION_WIN7)
		ret = synthvid_negotiate_ver(hdev, SYNTHVID_VERSION_WIN7);
	else
		ret = synthvid_negotiate_ver(hdev, SYNTHVID_VERSION_WIN8);

	if (ret) {
		pr_err("Synthetic video device version not accepted\n");
		goto error;
	}

	if (par->synthvid_version == SYNTHVID_VERSION_WIN7)
		screen_depth = SYNTHVID_DEPTH_WIN7;
	else
		screen_depth = SYNTHVID_DEPTH_WIN8;

	screen_fb_size = hdev->channel->offermsg.offer.
				mmio_megabytes * 1024 * 1024;

	return 0;

error:
	vmbus_close(hdev->channel);
	return ret;
}