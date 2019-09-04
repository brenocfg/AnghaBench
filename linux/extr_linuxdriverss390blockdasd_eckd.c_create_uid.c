#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dasd_uid {scalar_t__ type; scalar_t__ vduit; int /*<<< orphan*/  base_unit_addr; int /*<<< orphan*/  real_unit_addr; int /*<<< orphan*/  ssid; int /*<<< orphan*/  serial; int /*<<< orphan*/  vendor; } ;
struct dasd_eckd_private {TYPE_4__* vdsneq; TYPE_3__* sneq; TYPE_2__* ned; TYPE_1__* gneq; struct dasd_uid uid; } ;
struct TYPE_8__ {int* uit; } ;
struct TYPE_7__ {scalar_t__ sua_flags; int /*<<< orphan*/  base_unit_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  unit_addr; int /*<<< orphan*/  HDA_location; int /*<<< orphan*/  HDA_manufacturer; } ;
struct TYPE_5__ {int /*<<< orphan*/  subsystemID; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (int /*<<< orphan*/ ,int) ; 
 scalar_t__ UA_BASE_DEVICE ; 
 scalar_t__ UA_BASE_PAV_ALIAS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct dasd_uid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (scalar_t__,char*,int) ; 

__attribute__((used)) static void create_uid(struct dasd_eckd_private *private)
{
	int count;
	struct dasd_uid *uid;

	uid = &private->uid;
	memset(uid, 0, sizeof(struct dasd_uid));
	memcpy(uid->vendor, private->ned->HDA_manufacturer,
	       sizeof(uid->vendor) - 1);
	EBCASC(uid->vendor, sizeof(uid->vendor) - 1);
	memcpy(uid->serial, private->ned->HDA_location,
	       sizeof(uid->serial) - 1);
	EBCASC(uid->serial, sizeof(uid->serial) - 1);
	uid->ssid = private->gneq->subsystemID;
	uid->real_unit_addr = private->ned->unit_addr;
	if (private->sneq) {
		uid->type = private->sneq->sua_flags;
		if (uid->type == UA_BASE_PAV_ALIAS)
			uid->base_unit_addr = private->sneq->base_unit_addr;
	} else {
		uid->type = UA_BASE_DEVICE;
	}
	if (private->vdsneq) {
		for (count = 0; count < 16; count++) {
			sprintf(uid->vduit+2*count, "%02x",
				private->vdsneq->uit[count]);
		}
	}
}