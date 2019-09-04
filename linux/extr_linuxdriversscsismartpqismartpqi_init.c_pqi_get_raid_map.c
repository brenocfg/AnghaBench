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
struct raid_map {int dummy; } ;
struct pqi_scsi_dev {struct raid_map* raid_map; int /*<<< orphan*/  scsi3addr; } ;
struct pqi_raid_path_request {int /*<<< orphan*/  sg_descriptors; int /*<<< orphan*/  header; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_GET_RAID_MAP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int /*<<< orphan*/  kfree (struct raid_map*) ; 
 struct raid_map* kmalloc (int,int /*<<< orphan*/ ) ; 
 int pqi_build_raid_path_request (struct pqi_ctrl_info*,struct pqi_raid_path_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct raid_map*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pqi_pci_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int pqi_submit_raid_request_synchronous (struct pqi_ctrl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pqi_validate_raid_map (struct pqi_ctrl_info*,struct pqi_scsi_dev*,struct raid_map*) ; 

__attribute__((used)) static int pqi_get_raid_map(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device)
{
	int rc;
	int pci_direction;
	struct pqi_raid_path_request request;
	struct raid_map *raid_map;

	raid_map = kmalloc(sizeof(*raid_map), GFP_KERNEL);
	if (!raid_map)
		return -ENOMEM;

	rc = pqi_build_raid_path_request(ctrl_info, &request,
		CISS_GET_RAID_MAP, device->scsi3addr, raid_map,
		sizeof(*raid_map), 0, &pci_direction);
	if (rc)
		goto error;

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header, 0,
		NULL, NO_TIMEOUT);

	pqi_pci_unmap(ctrl_info->pci_dev, request.sg_descriptors, 1,
		pci_direction);

	if (rc)
		goto error;

	rc = pqi_validate_raid_map(ctrl_info, device, raid_map);
	if (rc)
		goto error;

	device->raid_map = raid_map;

	return 0;

error:
	kfree(raid_map);

	return rc;
}