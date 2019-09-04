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
struct pqi_raid_path_request {int /*<<< orphan*/  sg_descriptors; int /*<<< orphan*/  header; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMIC_WRITE_HOST_WELLNESS ; 
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int /*<<< orphan*/  RAID_CTLR_LUNID ; 
 int pqi_build_raid_path_request (struct pqi_ctrl_info*,struct pqi_raid_path_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pqi_pci_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int pqi_submit_raid_request_synchronous (struct pqi_ctrl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pqi_write_host_wellness(struct pqi_ctrl_info *ctrl_info,
	void *buffer, size_t buffer_length)
{
	int rc;
	struct pqi_raid_path_request request;
	int pci_direction;

	rc = pqi_build_raid_path_request(ctrl_info, &request,
		BMIC_WRITE_HOST_WELLNESS, RAID_CTLR_LUNID, buffer,
		buffer_length, 0, &pci_direction);
	if (rc)
		return rc;

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header,
		0, NULL, NO_TIMEOUT);

	pqi_pci_unmap(ctrl_info->pci_dev, request.sg_descriptors, 1,
		pci_direction);

	return rc;
}