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
typedef  int /*<<< orphan*/  u8 ;
struct esas2r_sg_context {int /*<<< orphan*/ * cur_offset; int /*<<< orphan*/  length; } ;
struct esas2r_request {struct esas2r_flash_context* interrupt_cx; int /*<<< orphan*/  req_stat; } ;
struct esas2r_flash_img {int fi_version; int action; int length; struct esas2r_component_header* cmp_hdr; int /*<<< orphan*/  num_comps; struct esas2r_sg_context* rel_version; int /*<<< orphan*/  flags; int /*<<< orphan*/  adap_typ; int /*<<< orphan*/  checksum; int /*<<< orphan*/  status; int /*<<< orphan*/  scratch_buf; } ;
struct esas2r_flash_context {int fi_hdr_len; size_t comp_typ; int /*<<< orphan*/  num_comps; int /*<<< orphan*/  interrupt_cb; struct esas2r_sg_context sgc; int /*<<< orphan*/  flsh_addr; int /*<<< orphan*/  func; int /*<<< orphan*/  task; int /*<<< orphan*/  scratch; int /*<<< orphan*/ * sgc_offset; struct esas2r_flash_img* fi; } ;
struct esas2r_component_header {int version; int /*<<< orphan*/  status; int /*<<< orphan*/ * pad; int /*<<< orphan*/  image_offset; int /*<<< orphan*/  length; int /*<<< orphan*/  img_type; } ;
struct esas2r_adapter {int flash_ver; struct esas2r_sg_context* image_type; int /*<<< orphan*/  flags; struct esas2r_flash_context flash_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_DEGRADED_MODE ; 
 int /*<<< orphan*/  AF_FLASH_LOCK ; 
 size_t CH_IT_BIOS ; 
 size_t CH_IT_CFG ; 
 size_t CH_IT_EFI ; 
 size_t CH_IT_MAC ; 
 int /*<<< orphan*/  CH_STAT_PENDING ; 
 int /*<<< orphan*/  CH_STAT_SUCCESS ; 
#define  FI_ACT_DOWN 131 
#define  FI_ACT_UP 130 
#define  FI_ACT_UPSZ 129 
 int /*<<< orphan*/  FI_NUM_COMPS_V1 ; 
 int /*<<< orphan*/  FI_STAT_BUSY ; 
 int /*<<< orphan*/  FI_STAT_DEGRADED ; 
 int /*<<< orphan*/  FI_STAT_FAILED ; 
 int /*<<< orphan*/  FI_STAT_IMG_VER ; 
 int /*<<< orphan*/  FI_STAT_INVALID ; 
 int /*<<< orphan*/  FI_STAT_SUCCESS ; 
#define  FI_VERSION_1 128 
 int /*<<< orphan*/  FLS_LENGTH_BOOT ; 
 int /*<<< orphan*/  FLS_OFFSET_BOOT ; 
 int /*<<< orphan*/  FMTSK_ERASE_BOOT ; 
 int /*<<< orphan*/  RS_SUCCESS ; 
 int /*<<< orphan*/  VDA_FLASH_BEGINW ; 
 int /*<<< orphan*/  calc_fi_checksum (struct esas2r_flash_context*) ; 
 int complete_fmapi_req (struct esas2r_adapter*,struct esas2r_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_disable_heartbeat (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_start_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  fix_bios (struct esas2r_adapter*,struct esas2r_flash_img*) ; 
 int /*<<< orphan*/  fix_efi (struct esas2r_adapter*,struct esas2r_flash_img*) ; 
 int /*<<< orphan*/  fw_download_proc ; 
 int /*<<< orphan*/  get_fi_adap_type (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  load_image (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  memcpy (struct esas2r_sg_context*,struct esas2r_sg_context*,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_fi (struct esas2r_adapter*,struct esas2r_flash_context*) ; 

bool esas2r_fm_api(struct esas2r_adapter *a, struct esas2r_flash_img *fi,
		   struct esas2r_request *rq, struct esas2r_sg_context *sgc)
{
	struct esas2r_flash_context *fc = &a->flash_context;
	u8 j;
	struct esas2r_component_header *ch;

	if (test_and_set_bit(AF_FLASH_LOCK, &a->flags)) {
		/* flag was already set */
		fi->status = FI_STAT_BUSY;
		return false;
	}

	memcpy(&fc->sgc, sgc, sizeof(struct esas2r_sg_context));
	sgc = &fc->sgc;
	fc->fi = fi;
	fc->sgc_offset = sgc->cur_offset;
	rq->req_stat = RS_SUCCESS;
	rq->interrupt_cx = fc;

	switch (fi->fi_version) {
	case FI_VERSION_1:
		fc->scratch = ((struct esas2r_flash_img *)fi)->scratch_buf;
		fc->num_comps = FI_NUM_COMPS_V1;
		fc->fi_hdr_len = sizeof(struct esas2r_flash_img);
		break;

	default:
		return complete_fmapi_req(a, rq, FI_STAT_IMG_VER);
	}

	if (test_bit(AF_DEGRADED_MODE, &a->flags))
		return complete_fmapi_req(a, rq, FI_STAT_DEGRADED);

	switch (fi->action) {
	case FI_ACT_DOWN: /* Download the components */
		/* Verify the format of the flash image */
		if (!verify_fi(a, fc))
			return complete_fmapi_req(a, rq, fi->status);

		/* Adjust the BIOS fields that are dependent on the HBA */
		ch = &fi->cmp_hdr[CH_IT_BIOS];

		if (ch->length)
			fix_bios(a, fi);

		/* Adjust the EFI fields that are dependent on the HBA */
		ch = &fi->cmp_hdr[CH_IT_EFI];

		if (ch->length)
			fix_efi(a, fi);

		/*
		 * Since the image was just modified, compute the checksum on
		 * the modified image.  First update the CRC for the composite
		 * expansion ROM image.
		 */
		fi->checksum = calc_fi_checksum(fc);

		/* Disable the heartbeat */
		esas2r_disable_heartbeat(a);

		/* Now start up the download sequence */
		fc->task = FMTSK_ERASE_BOOT;
		fc->func = VDA_FLASH_BEGINW;
		fc->comp_typ = CH_IT_CFG;
		fc->flsh_addr = FLS_OFFSET_BOOT;
		fc->sgc.length = FLS_LENGTH_BOOT;
		fc->sgc.cur_offset = NULL;

		/* Setup the callback address */
		fc->interrupt_cb = fw_download_proc;
		break;

	case FI_ACT_UPSZ: /* Get upload sizes */
		fi->adap_typ = get_fi_adap_type(a);
		fi->flags = 0;
		fi->num_comps = fc->num_comps;
		fi->length = fc->fi_hdr_len;

		/* Report the type of boot image in the rel_version string */
		memcpy(fi->rel_version, a->image_type,
		       sizeof(fi->rel_version));

		/* Build the component headers */
		for (j = 0, ch = fi->cmp_hdr;
		     j < fi->num_comps;
		     j++, ch++) {
			ch->img_type = j;
			ch->status = CH_STAT_PENDING;
			ch->length = 0;
			ch->version = 0xffffffff;
			ch->image_offset = 0;
			ch->pad[0] = 0;
			ch->pad[1] = 0;
		}

		if (a->flash_ver != 0) {
			fi->cmp_hdr[CH_IT_BIOS].version =
				fi->cmp_hdr[CH_IT_MAC].version =
					fi->cmp_hdr[CH_IT_EFI].version =
						fi->cmp_hdr[CH_IT_CFG].version
							= a->flash_ver;

			fi->cmp_hdr[CH_IT_BIOS].status =
				fi->cmp_hdr[CH_IT_MAC].status =
					fi->cmp_hdr[CH_IT_EFI].status =
						fi->cmp_hdr[CH_IT_CFG].status =
							CH_STAT_SUCCESS;

			return complete_fmapi_req(a, rq, FI_STAT_SUCCESS);
		}

	/* fall through */

	case FI_ACT_UP: /* Upload the components */
	default:
		return complete_fmapi_req(a, rq, FI_STAT_INVALID);
	}

	/*
	 * If we make it here, fc has been setup to do the first task.  Call
	 * load_image to format the request, start it, and get out.  The
	 * interrupt code will call the callback when the first message is
	 * complete.
	 */
	if (!load_image(a, rq))
		return complete_fmapi_req(a, rq, FI_STAT_FAILED);

	esas2r_start_request(a, rq);

	return true;
}