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
typedef  int u32 ;
struct b43_request_fw_context {int req_type; char* fwname; TYPE_3__* blob; int /*<<< orphan*/ * errors; TYPE_2__* dev; } ;
struct b43_fw_header {int type; int ver; int /*<<< orphan*/  size; } ;
struct b43_firmware_file {char const* filename; int type; TYPE_3__* data; } ;
struct TYPE_7__ {int size; scalar_t__ data; } ;
struct TYPE_6__ {TYPE_1__* dev; int /*<<< orphan*/  fw_load_complete; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  B43_FWTYPE_OPENSOURCE 132 
#define  B43_FWTYPE_PROPRIETARY 131 
#define  B43_FW_TYPE_IV 130 
#define  B43_FW_TYPE_PCM 129 
#define  B43_FW_TYPE_UCODE 128 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int ENOENT ; 
 int ENOSYS ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  b43_do_release_fw (struct b43_firmware_file*) ; 
 int /*<<< orphan*/  b43_fw_cb ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 char* modparam_fwpostfix ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  release_firmware (TYPE_3__*) ; 
 int request_firmware (TYPE_3__**,char*,int /*<<< orphan*/ ) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct b43_request_fw_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int b43_do_request_fw(struct b43_request_fw_context *ctx,
		      const char *name,
		      struct b43_firmware_file *fw, bool async)
{
	struct b43_fw_header *hdr;
	u32 size;
	int err;

	if (!name) {
		/* Don't fetch anything. Free possibly cached firmware. */
		/* FIXME: We should probably keep it anyway, to save some headache
		 * on suspend/resume with multiband devices. */
		b43_do_release_fw(fw);
		return 0;
	}
	if (fw->filename) {
		if ((fw->type == ctx->req_type) &&
		    (strcmp(fw->filename, name) == 0))
			return 0; /* Already have this fw. */
		/* Free the cached firmware first. */
		/* FIXME: We should probably do this later after we successfully
		 * got the new fw. This could reduce headache with multiband devices.
		 * We could also redesign this to cache the firmware for all possible
		 * bands all the time. */
		b43_do_release_fw(fw);
	}

	switch (ctx->req_type) {
	case B43_FWTYPE_PROPRIETARY:
		snprintf(ctx->fwname, sizeof(ctx->fwname),
			 "b43%s/%s.fw",
			 modparam_fwpostfix, name);
		break;
	case B43_FWTYPE_OPENSOURCE:
		snprintf(ctx->fwname, sizeof(ctx->fwname),
			 "b43-open%s/%s.fw",
			 modparam_fwpostfix, name);
		break;
	default:
		B43_WARN_ON(1);
		return -ENOSYS;
	}
	if (async) {
		/* do this part asynchronously */
		init_completion(&ctx->dev->fw_load_complete);
		err = request_firmware_nowait(THIS_MODULE, 1, ctx->fwname,
					      ctx->dev->dev->dev, GFP_KERNEL,
					      ctx, b43_fw_cb);
		if (err < 0) {
			pr_err("Unable to load firmware\n");
			return err;
		}
		wait_for_completion(&ctx->dev->fw_load_complete);
		if (ctx->blob)
			goto fw_ready;
	/* On some ARM systems, the async request will fail, but the next sync
	 * request works. For this reason, we fall through here
	 */
	}
	err = request_firmware(&ctx->blob, ctx->fwname,
			       ctx->dev->dev->dev);
	if (err == -ENOENT) {
		snprintf(ctx->errors[ctx->req_type],
			 sizeof(ctx->errors[ctx->req_type]),
			 "Firmware file \"%s\" not found\n",
			 ctx->fwname);
		return err;
	} else if (err) {
		snprintf(ctx->errors[ctx->req_type],
			 sizeof(ctx->errors[ctx->req_type]),
			 "Firmware file \"%s\" request failed (err=%d)\n",
			 ctx->fwname, err);
		return err;
	}
fw_ready:
	if (ctx->blob->size < sizeof(struct b43_fw_header))
		goto err_format;
	hdr = (struct b43_fw_header *)(ctx->blob->data);
	switch (hdr->type) {
	case B43_FW_TYPE_UCODE:
	case B43_FW_TYPE_PCM:
		size = be32_to_cpu(hdr->size);
		if (size != ctx->blob->size - sizeof(struct b43_fw_header))
			goto err_format;
		/* fallthrough */
	case B43_FW_TYPE_IV:
		if (hdr->ver != 1)
			goto err_format;
		break;
	default:
		goto err_format;
	}

	fw->data = ctx->blob;
	fw->filename = name;
	fw->type = ctx->req_type;

	return 0;

err_format:
	snprintf(ctx->errors[ctx->req_type],
		 sizeof(ctx->errors[ctx->req_type]),
		 "Firmware file \"%s\" format error.\n", ctx->fwname);
	release_firmware(ctx->blob);

	return -EPROTO;
}