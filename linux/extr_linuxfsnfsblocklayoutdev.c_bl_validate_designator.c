#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int designator_type; int designator_len; int /*<<< orphan*/  code_set; } ;
struct pnfs_block_volume {TYPE_1__ scsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_CODE_SET_BINARY ; 
#define  PS_DESIGNATOR_EUI64 131 
#define  PS_DESIGNATOR_NAA 130 
#define  PS_DESIGNATOR_NAME 129 
#define  PS_DESIGNATOR_T10 128 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
bl_validate_designator(struct pnfs_block_volume *v)
{
	switch (v->scsi.designator_type) {
	case PS_DESIGNATOR_EUI64:
		if (v->scsi.code_set != PS_CODE_SET_BINARY)
			return false;

		if (v->scsi.designator_len != 8 &&
		    v->scsi.designator_len != 10 &&
		    v->scsi.designator_len != 16)
			return false;

		return true;
	case PS_DESIGNATOR_NAA:
		if (v->scsi.code_set != PS_CODE_SET_BINARY)
			return false;

		if (v->scsi.designator_len != 8 &&
		    v->scsi.designator_len != 16)
			return false;

		return true;
	case PS_DESIGNATOR_T10:
	case PS_DESIGNATOR_NAME:
		pr_err("pNFS: unsupported designator "
			"(code set %d, type %d, len %d.\n",
			v->scsi.code_set,
			v->scsi.designator_type,
			v->scsi.designator_len);
		return false;
	default:
		pr_err("pNFS: invalid designator "
			"(code set %d, type %d, len %d.\n",
			v->scsi.code_set,
			v->scsi.designator_type,
			v->scsi.designator_len);
		return false;
	}
}