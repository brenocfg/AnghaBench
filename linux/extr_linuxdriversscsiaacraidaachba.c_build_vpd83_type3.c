#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int codeset; int identifiertype; int identifierlength; int /*<<< orphan*/  Identifier; } ;
struct tvpd_page83 {TYPE_2__ type3; } ;
struct scsi_cmnd {int dummy; } ;
struct aac_dev {int maximum_num_containers; TYPE_1__* fsa_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  identifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static void build_vpd83_type3(struct tvpd_page83 *vpdpage83data,
		struct aac_dev *dev, struct scsi_cmnd *scsicmd)
{
	int container;

	vpdpage83data->type3.codeset = 1;
	vpdpage83data->type3.identifiertype = 3;
	vpdpage83data->type3.identifierlength = sizeof(vpdpage83data->type3)
			- 4;

	for (container = 0; container < dev->maximum_num_containers;
			container++) {

		if (scmd_id(scsicmd) == container) {
			memcpy(vpdpage83data->type3.Identifier,
					dev->fsa_dev[container].identifier,
					16);
			break;
		}
	}
}