#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct firmware {int dummy; } ;
struct brcmf_fw_item {char* path; scalar_t__ type; struct firmware const* binary; } ;
struct brcmf_fw {size_t curpos; int /*<<< orphan*/  dev; TYPE_1__* req; } ;
struct TYPE_2__ {struct brcmf_fw_item* items; } ;

/* Variables and functions */
 scalar_t__ BRCMF_FW_TYPE_BINARY ; 
 scalar_t__ BRCMF_FW_TYPE_NVRAM ; 
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  brcmf_fw_request_done (int /*<<< orphan*/ *,struct brcmf_fw*) ; 
 int /*<<< orphan*/  brcmf_fw_request_nvram_done (struct firmware const*,struct brcmf_fw*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcmf_fw*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,struct brcmf_fw*)) ; 

__attribute__((used)) static int brcmf_fw_request_next_item(struct brcmf_fw *fwctx, bool async)
{
	struct brcmf_fw_item *cur;
	const struct firmware *fw = NULL;
	int ret;

	cur = &fwctx->req->items[fwctx->curpos];

	brcmf_dbg(TRACE, "%srequest for %s\n", async ? "async " : "",
		  cur->path);

	if (async)
		ret = request_firmware_nowait(THIS_MODULE, true, cur->path,
					      fwctx->dev, GFP_KERNEL, fwctx,
					      brcmf_fw_request_done);
	else
		ret = request_firmware(&fw, cur->path, fwctx->dev);

	if (ret < 0) {
		brcmf_fw_request_done(NULL, fwctx);
	} else if (!async && fw) {
		brcmf_dbg(TRACE, "firmware %s %sfound\n", cur->path,
			  fw ? "" : "not ");
		if (cur->type == BRCMF_FW_TYPE_BINARY)
			cur->binary = fw;
		else if (cur->type == BRCMF_FW_TYPE_NVRAM)
			brcmf_fw_request_nvram_done(fw, fwctx);
		else
			release_firmware(fw);

		return -EAGAIN;
	}
	return 0;
}