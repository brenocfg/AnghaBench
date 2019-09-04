#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  cmd_rsp_len; } ;
struct atto_vda_cfg_rsp {int /*<<< orphan*/  fw_release; int /*<<< orphan*/  fw_build; int /*<<< orphan*/  vda_version; } ;
struct TYPE_26__ {int /*<<< orphan*/  length; int /*<<< orphan*/  dev_index; int /*<<< orphan*/  scan_generation; } ;
struct TYPE_25__ {int /*<<< orphan*/  file_size; } ;
struct TYPE_20__ {TYPE_13__ cli_rsp; struct atto_vda_cfg_rsp cfg_rsp; TYPE_5__ mgt_rsp; TYPE_4__ flash_rsp; } ;
struct esas2r_request {TYPE_14__ func_rsp; TYPE_10__* vrq; int /*<<< orphan*/  req_stat; scalar_t__ interrupt_cx; } ;
struct esas2r_adapter {int dummy; } ;
struct atto_vda_cfg_init {int dummy; } ;
struct TYPE_29__ {int /*<<< orphan*/  fw_release; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  fw_build; void* vda_version; } ;
struct TYPE_21__ {TYPE_8__ init; } ;
struct atto_ioctl_vda_cfg_cmd {TYPE_15__ data; int /*<<< orphan*/  data_length; int /*<<< orphan*/  cfg_func; } ;
struct TYPE_17__ {void* cmd_rsp_len; } ;
struct TYPE_28__ {int /*<<< orphan*/  data; void* data_length; int /*<<< orphan*/  dev_index; int /*<<< orphan*/  scan_generation; } ;
struct TYPE_22__ {void* file_size; } ;
struct TYPE_23__ {TYPE_1__ file; } ;
struct TYPE_24__ {TYPE_2__ data; int /*<<< orphan*/  sub_func; } ;
struct TYPE_18__ {TYPE_11__ cli; struct atto_ioctl_vda_cfg_cmd cfg; TYPE_7__ mgt; TYPE_3__ flash; } ;
struct atto_ioctl_vda {int function; TYPE_12__ cmd; int /*<<< orphan*/  data_length; int /*<<< orphan*/  vda_status; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_30__ {int /*<<< orphan*/  sub_func; } ;
struct TYPE_27__ {int /*<<< orphan*/  mgt_func; } ;
struct TYPE_16__ {TYPE_9__ cfg; TYPE_6__ mgt; } ;

/* Variables and functions */
 scalar_t__ HIBYTE (int /*<<< orphan*/ ) ; 
 scalar_t__ LOBYTE (int /*<<< orphan*/ ) ; 
 char LOWORD (scalar_t__) ; 
 int /*<<< orphan*/  VDA_CFG_GET_INIT ; 
 int /*<<< orphan*/  VDA_FLASH_FINFO ; 
 int /*<<< orphan*/  VDA_FLASH_FREAD ; 
#define  VDA_FUNC_CFG 131 
#define  VDA_FUNC_CLI 130 
#define  VDA_FUNC_FLASH 129 
#define  VDA_FUNC_MGT 128 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  esas2r_nuxi_cfg_data (int /*<<< orphan*/ ,TYPE_15__*) ; 
 int /*<<< orphan*/  esas2r_nuxi_mgt_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static void esas2r_complete_vda_ioctl(struct esas2r_adapter *a,
				      struct esas2r_request *rq)
{
	struct atto_ioctl_vda *vi = (struct atto_ioctl_vda *)rq->interrupt_cx;

	vi->vda_status = rq->req_stat;

	switch (vi->function) {
	case VDA_FUNC_FLASH:

		if (vi->cmd.flash.sub_func == VDA_FLASH_FINFO
		    || vi->cmd.flash.sub_func == VDA_FLASH_FREAD)
			vi->cmd.flash.data.file.file_size =
				le32_to_cpu(rq->func_rsp.flash_rsp.file_size);

		break;

	case VDA_FUNC_MGT:

		vi->cmd.mgt.scan_generation =
			rq->func_rsp.mgt_rsp.scan_generation;
		vi->cmd.mgt.dev_index = le16_to_cpu(
			rq->func_rsp.mgt_rsp.dev_index);

		if (vi->data_length == 0)
			vi->cmd.mgt.data_length =
				le32_to_cpu(rq->func_rsp.mgt_rsp.length);

		esas2r_nuxi_mgt_data(rq->vrq->mgt.mgt_func, &vi->cmd.mgt.data);
		break;

	case VDA_FUNC_CFG:

		if (vi->cmd.cfg.cfg_func == VDA_CFG_GET_INIT) {
			struct atto_ioctl_vda_cfg_cmd *cfg = &vi->cmd.cfg;
			struct atto_vda_cfg_rsp *rsp = &rq->func_rsp.cfg_rsp;
			char buf[sizeof(cfg->data.init.fw_release) + 1];

			cfg->data_length =
				cpu_to_le32(sizeof(struct atto_vda_cfg_init));
			cfg->data.init.vda_version =
				le32_to_cpu(rsp->vda_version);
			cfg->data.init.fw_build = rsp->fw_build;

			snprintf(buf, sizeof(buf), "%1.1u.%2.2u",
				 (int)LOBYTE(le16_to_cpu(rsp->fw_release)),
				 (int)HIBYTE(le16_to_cpu(rsp->fw_release)));

			memcpy(&cfg->data.init.fw_release, buf,
			       sizeof(cfg->data.init.fw_release));

			if (LOWORD(LOBYTE(cfg->data.init.fw_build)) == 'A')
				cfg->data.init.fw_version =
					cfg->data.init.fw_build;
			else
				cfg->data.init.fw_version =
					cfg->data.init.fw_release;
		} else {
			esas2r_nuxi_cfg_data(rq->vrq->cfg.sub_func,
					     &vi->cmd.cfg.data);
		}

		break;

	case VDA_FUNC_CLI:

		vi->cmd.cli.cmd_rsp_len =
			le32_to_cpu(rq->func_rsp.cli_rsp.cmd_rsp_len);
		break;

	default:

		break;
	}
}