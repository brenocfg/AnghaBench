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
typedef  int u8 ;
struct svc_export {int ex_flags; int /*<<< orphan*/ * ex_uuid; } ;
struct TYPE_4__ {TYPE_1__* s_type; int /*<<< orphan*/  s_dev; } ;
struct TYPE_3__ {int fs_flags; } ;

/* Variables and functions */
#define  FSID_DEV 135 
#define  FSID_ENCODE_DEV 134 
#define  FSID_MAJOR_MINOR 133 
#define  FSID_NUM 132 
#define  FSID_UUID16 131 
#define  FSID_UUID16_INUM 130 
#define  FSID_UUID4_INUM 129 
#define  FSID_UUID8 128 
 int FS_REQUIRES_DEV ; 
 int NFSEXP_FSID ; 
 TYPE_2__* exp_sb (struct svc_export*) ; 
 int /*<<< orphan*/  is_root_export (struct svc_export*) ; 
 int /*<<< orphan*/  old_valid_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fsid_type_ok_for_exp(u8 fsid_type, struct svc_export *exp)
{
	switch (fsid_type) {
	case FSID_DEV:
		if (!old_valid_dev(exp_sb(exp)->s_dev))
			return false;
		/* FALL THROUGH */
	case FSID_MAJOR_MINOR:
	case FSID_ENCODE_DEV:
		return exp_sb(exp)->s_type->fs_flags & FS_REQUIRES_DEV;
	case FSID_NUM:
		return exp->ex_flags & NFSEXP_FSID;
	case FSID_UUID8:
	case FSID_UUID16:
		if (!is_root_export(exp))
			return false;
		/* fall through */
	case FSID_UUID4_INUM:
	case FSID_UUID16_INUM:
		return exp->ex_uuid != NULL;
	}
	return true;
}