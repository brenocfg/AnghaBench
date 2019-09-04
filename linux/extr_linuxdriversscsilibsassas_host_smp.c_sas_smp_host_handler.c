#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sas_ha_struct {int num_phys; } ;
struct TYPE_6__ {int payload_len; int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct TYPE_5__ {int payload_len; int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {TYPE_3__ reply_payload; TYPE_2__ request_payload; } ;
struct Scsi_Host {TYPE_1__* hostt; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SAS_EXPANDER_PRODUCT_ID_LEN ; 
 int /*<<< orphan*/  SAS_EXPANDER_VENDOR_ID_LEN ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
#define  SMP_CONF_ROUTE_INFO 138 
#define  SMP_DISCOVER 137 
#define  SMP_PHY_CONTROL 136 
#define  SMP_PHY_TEST_FUNCTION 135 
#define  SMP_READ_GPIO_REG 134 
#define  SMP_REPORT_GENERAL 133 
#define  SMP_REPORT_MANUF_INFO 132 
#define  SMP_REPORT_PHY_ERR_LOG 131 
#define  SMP_REPORT_PHY_SATA 130 
#define  SMP_REPORT_ROUTE_INFO 129 
 int SMP_REQUEST ; 
 int SMP_RESPONSE ; 
 int SMP_RESP_FUNC_ACC ; 
 int SMP_RESP_FUNC_UNK ; 
 int SMP_RESP_INV_FRM_LEN ; 
#define  SMP_WRITE_GPIO_REG 128 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,unsigned int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max (int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_host_smp_discover (struct sas_ha_struct*,int*,int) ; 
 int sas_host_smp_write_gpio (struct sas_ha_struct*,int*,int,int,int,int*) ; 
 int /*<<< orphan*/  sas_phy_control (struct sas_ha_struct*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  sas_report_phy_sata (struct sas_ha_struct*,int*,int) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

void sas_smp_host_handler(struct bsg_job *job, struct Scsi_Host *shost)
{
	struct sas_ha_struct *sas_ha = SHOST_TO_SAS_HA(shost);
	u8 *req_data, *resp_data;
	unsigned int reslen = 0;
	int error = -EINVAL;

	/* eight is the minimum size for request and response frames */
	if (job->request_payload.payload_len < 8 ||
	    job->reply_payload.payload_len < 8)
		goto out;

	error = -ENOMEM;
	req_data = kzalloc(job->request_payload.payload_len, GFP_KERNEL);
	if (!req_data)
		goto out;
	sg_copy_to_buffer(job->request_payload.sg_list,
			  job->request_payload.sg_cnt, req_data,
			  job->request_payload.payload_len);

	/* make sure frame can always be built ... we copy
	 * back only the requested length */
	resp_data = kzalloc(max(job->reply_payload.payload_len, 128U),
			GFP_KERNEL);
	if (!resp_data)
		goto out_free_req;

	error = -EINVAL;
	if (req_data[0] != SMP_REQUEST)
		goto out_free_resp;

	/* set up default don't know response */
	resp_data[0] = SMP_RESPONSE;
	resp_data[1] = req_data[1];
	resp_data[2] = SMP_RESP_FUNC_UNK;

	switch (req_data[1]) {
	case SMP_REPORT_GENERAL:
		resp_data[2] = SMP_RESP_FUNC_ACC;
		resp_data[9] = sas_ha->num_phys;
		reslen = 32;
		break;

	case SMP_REPORT_MANUF_INFO:
		resp_data[2] = SMP_RESP_FUNC_ACC;
		memcpy(resp_data + 12, shost->hostt->name,
		       SAS_EXPANDER_VENDOR_ID_LEN);
		memcpy(resp_data + 20, "libsas virt phy",
		       SAS_EXPANDER_PRODUCT_ID_LEN);
		reslen = 64;
		break;

	case SMP_READ_GPIO_REG:
		/* FIXME: need GPIO support in the transport class */
		break;

	case SMP_DISCOVER:
		if (job->request_payload.payload_len < 16)
			goto out_free_resp;
		sas_host_smp_discover(sas_ha, resp_data, req_data[9]);
		reslen = 56;
		break;

	case SMP_REPORT_PHY_ERR_LOG:
		/* FIXME: could implement this with additional
		 * libsas callbacks providing the HW supports it */
		break;

	case SMP_REPORT_PHY_SATA:
		if (job->request_payload.payload_len < 16)
			goto out_free_resp;
		sas_report_phy_sata(sas_ha, resp_data, req_data[9]);
		reslen = 60;
		break;

	case SMP_REPORT_ROUTE_INFO:
		/* Can't implement; hosts have no routes */
		break;

	case SMP_WRITE_GPIO_REG: {
		/* SFF-8485 v0.7 */
		const int base_frame_size = 11;
		int to_write = req_data[4];

		if (job->request_payload.payload_len <
				base_frame_size + to_write * 4) {
			resp_data[2] = SMP_RESP_INV_FRM_LEN;
			break;
		}

		to_write = sas_host_smp_write_gpio(sas_ha, resp_data, req_data[2],
						   req_data[3], to_write, &req_data[8]);
		reslen = 8;
		break;
	}

	case SMP_CONF_ROUTE_INFO:
		/* Can't implement; hosts have no routes */
		break;

	case SMP_PHY_CONTROL:
		if (job->request_payload.payload_len < 44)
			goto out_free_resp;
		sas_phy_control(sas_ha, req_data[9], req_data[10],
				req_data[32] >> 4, req_data[33] >> 4,
				resp_data);
		reslen = 8;
		break;

	case SMP_PHY_TEST_FUNCTION:
		/* FIXME: should this be implemented? */
		break;

	default:
		/* probably a 2.0 function */
		break;
	}

	sg_copy_from_buffer(job->reply_payload.sg_list,
			    job->reply_payload.sg_cnt, resp_data,
			    job->reply_payload.payload_len);

	error = 0;
out_free_resp:
	kfree(resp_data);
out_free_req:
	kfree(req_data);
out:
	bsg_job_done(job, error, reslen);
}