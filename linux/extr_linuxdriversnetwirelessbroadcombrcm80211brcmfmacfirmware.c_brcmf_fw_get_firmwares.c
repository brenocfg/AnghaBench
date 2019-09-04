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
struct device {int dummy; } ;
struct brcmf_fw_request {int dummy; } ;
struct brcmf_fw {void (* done ) (struct device*,int,struct brcmf_fw_request*) ;struct brcmf_fw_request* req; struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fw_request_is_valid (struct brcmf_fw_request*) ; 
 int /*<<< orphan*/  brcmf_fw_request_next_item (struct brcmf_fw*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct brcmf_fw* kzalloc (int,int /*<<< orphan*/ ) ; 

int brcmf_fw_get_firmwares(struct device *dev, struct brcmf_fw_request *req,
			   void (*fw_cb)(struct device *dev, int err,
					 struct brcmf_fw_request *req))
{
	struct brcmf_fw *fwctx;

	brcmf_dbg(TRACE, "enter: dev=%s\n", dev_name(dev));
	if (!fw_cb)
		return -EINVAL;

	if (!brcmf_fw_request_is_valid(req))
		return -EINVAL;

	fwctx = kzalloc(sizeof(*fwctx), GFP_KERNEL);
	if (!fwctx)
		return -ENOMEM;

	fwctx->dev = dev;
	fwctx->req = req;
	fwctx->done = fw_cb;

	brcmf_fw_request_next_item(fwctx, true);
	return 0;
}