#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct firmware {int dummy; } ;
struct brcmf_fw_item {int type; int flags; int /*<<< orphan*/  path; struct firmware const* binary; } ;
struct brcmf_fw {size_t curpos; TYPE_1__* req; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* done ) (int /*<<< orphan*/ ,int,TYPE_1__*) ;} ;
struct TYPE_3__ {size_t n_items; struct brcmf_fw_item* items; } ;

/* Variables and functions */
 int BRCMF_FW_REQF_OPTIONAL ; 
#define  BRCMF_FW_TYPE_BINARY 129 
#define  BRCMF_FW_TYPE_NVRAM 128 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int /*<<< orphan*/  brcmf_fw_free_request (TYPE_1__*) ; 
 int brcmf_fw_request_next_item (struct brcmf_fw*,int) ; 
 int brcmf_fw_request_nvram_done (struct firmware const*,struct brcmf_fw*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct brcmf_fw*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,TYPE_1__*) ; 

__attribute__((used)) static void brcmf_fw_request_done(const struct firmware *fw, void *ctx)
{
	struct brcmf_fw *fwctx = ctx;
	struct brcmf_fw_item *cur;
	int ret = 0;

	cur = &fwctx->req->items[fwctx->curpos];

	brcmf_dbg(TRACE, "enter: firmware %s %sfound\n", cur->path,
		  fw ? "" : "not ");

	if (!fw)
		ret = -ENOENT;

	switch (cur->type) {
	case BRCMF_FW_TYPE_NVRAM:
		ret = brcmf_fw_request_nvram_done(fw, fwctx);
		break;
	case BRCMF_FW_TYPE_BINARY:
		cur->binary = fw;
		break;
	default:
		/* something fishy here so bail out early */
		brcmf_err("unknown fw type: %d\n", cur->type);
		release_firmware(fw);
		ret = -EINVAL;
		goto fail;
	}

	if (ret < 0 && !(cur->flags & BRCMF_FW_REQF_OPTIONAL))
		goto fail;

	do {
		if (++fwctx->curpos == fwctx->req->n_items) {
			ret = 0;
			goto done;
		}

		ret = brcmf_fw_request_next_item(fwctx, false);
	} while (ret == -EAGAIN);

	return;

fail:
	brcmf_dbg(TRACE, "failed err=%d: dev=%s, fw=%s\n", ret,
		  dev_name(fwctx->dev), cur->path);
	brcmf_fw_free_request(fwctx->req);
	fwctx->req = NULL;
done:
	fwctx->done(fwctx->dev, ret, fwctx->req);
	kfree(fwctx);
}