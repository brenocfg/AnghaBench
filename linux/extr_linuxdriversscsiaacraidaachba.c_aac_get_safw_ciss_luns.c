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
typedef  void* u8 ;
struct aac_srb {int* cdb; int /*<<< orphan*/  flags; } ;
struct aac_srb_unit {struct aac_srb srb; } ;
struct aac_dev {struct aac_ciss_phys_luns_resp* safw_phys_luns; } ;
struct aac_ciss_phys_luns_resp {int resp_flag; } ;
struct _ciss_lun {int dummy; } ;

/* Variables and functions */
 int AAC_MAX_TARGETS ; 
 int CISS_REPORT_PHYSICAL_LUNS ; 
 int ENOMEM ; 
 int ENOMSG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SRB_DataIn ; 
 int aac_send_safw_bmic_cmd (struct aac_dev*,struct aac_srb_unit*,struct aac_ciss_phys_luns_resp*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aac_ciss_phys_luns_resp*) ; 
 struct aac_ciss_phys_luns_resp* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct aac_srb_unit*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aac_get_safw_ciss_luns(struct aac_dev *dev)
{
	int rcode = -ENOMEM;
	int datasize;
	struct aac_srb *srbcmd;
	struct aac_srb_unit srbu;
	struct aac_ciss_phys_luns_resp *phys_luns;

	datasize = sizeof(struct aac_ciss_phys_luns_resp) +
		(AAC_MAX_TARGETS - 1) * sizeof(struct _ciss_lun);
	phys_luns = kmalloc(datasize, GFP_KERNEL);
	if (phys_luns == NULL)
		goto out;

	memset(&srbu, 0, sizeof(struct aac_srb_unit));

	srbcmd = &srbu.srb;
	srbcmd->flags	= cpu_to_le32(SRB_DataIn);
	srbcmd->cdb[0]	= CISS_REPORT_PHYSICAL_LUNS;
	srbcmd->cdb[1]	= 2; /* extended reporting */
	srbcmd->cdb[8]	= (u8)(datasize >> 8);
	srbcmd->cdb[9]	= (u8)(datasize);

	rcode = aac_send_safw_bmic_cmd(dev, &srbu, phys_luns, datasize);
	if (unlikely(rcode < 0))
		goto mem_free_all;

	if (phys_luns->resp_flag != 2) {
		rcode = -ENOMSG;
		goto mem_free_all;
	}

	dev->safw_phys_luns = phys_luns;

out:
	return rcode;
mem_free_all:
	kfree(phys_luns);
	goto out;
}