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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioc; } ;
struct bfad_s {TYPE_1__ bfa; } ;
struct bfad_im_port_s {struct bfad_s* bfad; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int BFA_ADAPTER_MODEL_DESCR_LEN ; 
 int BFA_ADAPTER_MODEL_NAME_LEN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bfa_get_adapter_model (TYPE_1__*,char*) ; 
 int bfa_get_nports (TYPE_1__*) ; 
 scalar_t__ bfa_ioc_is_cna (int /*<<< orphan*/ *) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static ssize_t
bfad_im_model_desc_show(struct device *dev, struct device_attribute *attr,
				 char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct bfad_im_port_s *im_port =
			(struct bfad_im_port_s *) shost->hostdata[0];
	struct bfad_s *bfad = im_port->bfad;
	char model[BFA_ADAPTER_MODEL_NAME_LEN];
	char model_descr[BFA_ADAPTER_MODEL_DESCR_LEN];
	int nports = 0;

	bfa_get_adapter_model(&bfad->bfa, model);
	nports = bfa_get_nports(&bfad->bfa);
	if (!strcmp(model, "QLogic-425"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 4Gbps PCIe dual port FC HBA");
	else if (!strcmp(model, "QLogic-825"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 8Gbps PCIe dual port FC HBA");
	else if (!strcmp(model, "QLogic-42B"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 4Gbps PCIe dual port FC HBA for HP");
	else if (!strcmp(model, "QLogic-82B"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 8Gbps PCIe dual port FC HBA for HP");
	else if (!strcmp(model, "QLogic-1010"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 10Gbps single port CNA");
	else if (!strcmp(model, "QLogic-1020"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 10Gbps dual port CNA");
	else if (!strcmp(model, "QLogic-1007"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 10Gbps CNA for IBM Blade Center");
	else if (!strcmp(model, "QLogic-415"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 4Gbps PCIe single port FC HBA");
	else if (!strcmp(model, "QLogic-815"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 8Gbps PCIe single port FC HBA");
	else if (!strcmp(model, "QLogic-41B"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 4Gbps PCIe single port FC HBA for HP");
	else if (!strcmp(model, "QLogic-81B"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 8Gbps PCIe single port FC HBA for HP");
	else if (!strcmp(model, "QLogic-804"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 8Gbps FC HBA for HP Bladesystem C-class");
	else if (!strcmp(model, "QLogic-1741"))
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 10Gbps CNA for Dell M-Series Blade Servers");
	else if (strstr(model, "QLogic-1860")) {
		if (nports == 1 && bfa_ioc_is_cna(&bfad->bfa.ioc))
			snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 10Gbps single port CNA");
		else if (nports == 1 && !bfa_ioc_is_cna(&bfad->bfa.ioc))
			snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 16Gbps PCIe single port FC HBA");
		else if (nports == 2 && bfa_ioc_is_cna(&bfad->bfa.ioc))
			snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 10Gbps dual port CNA");
		else if (nports == 2 && !bfa_ioc_is_cna(&bfad->bfa.ioc))
			snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 16Gbps PCIe dual port FC HBA");
	} else if (!strcmp(model, "QLogic-1867")) {
		if (nports == 1 && !bfa_ioc_is_cna(&bfad->bfa.ioc))
			snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 16Gbps PCIe single port FC HBA for IBM");
		else if (nports == 2 && !bfa_ioc_is_cna(&bfad->bfa.ioc))
			snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 16Gbps PCIe dual port FC HBA for IBM");
	} else
		snprintf(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"Invalid Model");

	return snprintf(buf, PAGE_SIZE, "%s\n", model_descr);
}