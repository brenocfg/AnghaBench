#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_76__   TYPE_9__ ;
typedef  struct TYPE_75__   TYPE_8__ ;
typedef  struct TYPE_74__   TYPE_7__ ;
typedef  struct TYPE_73__   TYPE_6__ ;
typedef  struct TYPE_72__   TYPE_5__ ;
typedef  struct TYPE_71__   TYPE_4__ ;
typedef  struct TYPE_70__   TYPE_3__ ;
typedef  struct TYPE_69__   TYPE_38__ ;
typedef  struct TYPE_68__   TYPE_37__ ;
typedef  struct TYPE_67__   TYPE_36__ ;
typedef  struct TYPE_66__   TYPE_35__ ;
typedef  struct TYPE_65__   TYPE_34__ ;
typedef  struct TYPE_64__   TYPE_33__ ;
typedef  struct TYPE_63__   TYPE_32__ ;
typedef  struct TYPE_62__   TYPE_31__ ;
typedef  struct TYPE_61__   TYPE_30__ ;
typedef  struct TYPE_60__   TYPE_2__ ;
typedef  struct TYPE_59__   TYPE_29__ ;
typedef  struct TYPE_58__   TYPE_28__ ;
typedef  struct TYPE_57__   TYPE_27__ ;
typedef  struct TYPE_56__   TYPE_26__ ;
typedef  struct TYPE_55__   TYPE_25__ ;
typedef  struct TYPE_54__   TYPE_24__ ;
typedef  struct TYPE_53__   TYPE_23__ ;
typedef  struct TYPE_52__   TYPE_22__ ;
typedef  struct TYPE_51__   TYPE_21__ ;
typedef  struct TYPE_50__   TYPE_20__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_19__ ;
typedef  struct TYPE_47__   TYPE_18__ ;
typedef  struct TYPE_46__   TYPE_17__ ;
typedef  struct TYPE_45__   TYPE_16__ ;
typedef  struct TYPE_44__   TYPE_15__ ;
typedef  struct TYPE_43__   TYPE_14__ ;
typedef  struct TYPE_42__   TYPE_13__ ;
typedef  struct TYPE_41__   TYPE_12__ ;
typedef  struct TYPE_40__   TYPE_11__ ;
typedef  struct TYPE_39__   TYPE_10__ ;

/* Type definitions */
struct TYPE_66__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_67__ {TYPE_35__ refn; } ;
struct TYPE_64__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_65__ {TYPE_33__ refn; } ;
struct TYPE_62__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_63__ {TYPE_31__ refn; } ;
struct TYPE_59__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_61__ {TYPE_29__ refn; } ;
struct TYPE_57__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_58__ {TYPE_27__ refn; } ;
struct TYPE_56__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_54__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_55__ {TYPE_24__ refn; } ;
struct TYPE_52__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_53__ {TYPE_22__ refn; } ;
struct TYPE_51__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_48__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_50__ {TYPE_19__ old_parent_refn; } ;
struct TYPE_46__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_47__ {TYPE_17__ parent_refn; } ;
struct TYPE_44__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_45__ {TYPE_15__ refn; } ;
struct TYPE_42__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_43__ {TYPE_13__ refn; } ;
struct TYPE_40__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_41__ {TYPE_11__ parent_refn; } ;
struct TYPE_76__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_39__ {TYPE_9__ parent_refn; } ;
struct TYPE_74__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_75__ {TYPE_7__ refn; } ;
struct TYPE_72__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_73__ {TYPE_5__ parent_refn; } ;
struct TYPE_70__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_71__ {TYPE_3__ parent_refn; } ;
struct TYPE_49__ {int /*<<< orphan*/  fs_id; } ;
struct TYPE_60__ {TYPE_1__ refn; } ;
struct TYPE_68__ {TYPE_36__ fsync; TYPE_34__ removexattr; TYPE_32__ listxattr; TYPE_30__ setxattr; TYPE_28__ getxattr; TYPE_26__ fs_umount; TYPE_25__ ra_cache_flush; TYPE_23__ truncate; TYPE_21__ statfs; TYPE_20__ rename; TYPE_18__ sym; TYPE_16__ setattr; TYPE_14__ readdir; TYPE_12__ mkdir; TYPE_10__ remove; TYPE_8__ getattr; TYPE_6__ create; TYPE_4__ lookup; TYPE_2__ io; } ;
struct TYPE_69__ {int type; TYPE_37__ req; } ;
struct orangefs_kernel_op_s {TYPE_38__ upcall; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ORANGEFS_FS_ID_NULL ; 
#define  ORANGEFS_VFS_OP_CREATE 146 
#define  ORANGEFS_VFS_OP_FILE_IO 145 
#define  ORANGEFS_VFS_OP_FSYNC 144 
#define  ORANGEFS_VFS_OP_FS_UMOUNT 143 
#define  ORANGEFS_VFS_OP_GETATTR 142 
#define  ORANGEFS_VFS_OP_GETXATTR 141 
#define  ORANGEFS_VFS_OP_LISTXATTR 140 
#define  ORANGEFS_VFS_OP_LOOKUP 139 
#define  ORANGEFS_VFS_OP_MKDIR 138 
#define  ORANGEFS_VFS_OP_RA_FLUSH 137 
#define  ORANGEFS_VFS_OP_READDIR 136 
#define  ORANGEFS_VFS_OP_REMOVE 135 
#define  ORANGEFS_VFS_OP_REMOVEXATTR 134 
#define  ORANGEFS_VFS_OP_RENAME 133 
#define  ORANGEFS_VFS_OP_SETATTR 132 
#define  ORANGEFS_VFS_OP_SETXATTR 131 
#define  ORANGEFS_VFS_OP_STATFS 130 
#define  ORANGEFS_VFS_OP_SYMLINK 129 
#define  ORANGEFS_VFS_OP_TRUNCATE 128 

__s32 fsid_of_op(struct orangefs_kernel_op_s *op)
{
	__s32 fsid = ORANGEFS_FS_ID_NULL;

	if (op) {
		switch (op->upcall.type) {
		case ORANGEFS_VFS_OP_FILE_IO:
			fsid = op->upcall.req.io.refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_LOOKUP:
			fsid = op->upcall.req.lookup.parent_refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_CREATE:
			fsid = op->upcall.req.create.parent_refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_GETATTR:
			fsid = op->upcall.req.getattr.refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_REMOVE:
			fsid = op->upcall.req.remove.parent_refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_MKDIR:
			fsid = op->upcall.req.mkdir.parent_refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_READDIR:
			fsid = op->upcall.req.readdir.refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_SETATTR:
			fsid = op->upcall.req.setattr.refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_SYMLINK:
			fsid = op->upcall.req.sym.parent_refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_RENAME:
			fsid = op->upcall.req.rename.old_parent_refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_STATFS:
			fsid = op->upcall.req.statfs.fs_id;
			break;
		case ORANGEFS_VFS_OP_TRUNCATE:
			fsid = op->upcall.req.truncate.refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_RA_FLUSH:
			fsid = op->upcall.req.ra_cache_flush.refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_FS_UMOUNT:
			fsid = op->upcall.req.fs_umount.fs_id;
			break;
		case ORANGEFS_VFS_OP_GETXATTR:
			fsid = op->upcall.req.getxattr.refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_SETXATTR:
			fsid = op->upcall.req.setxattr.refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_LISTXATTR:
			fsid = op->upcall.req.listxattr.refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_REMOVEXATTR:
			fsid = op->upcall.req.removexattr.refn.fs_id;
			break;
		case ORANGEFS_VFS_OP_FSYNC:
			fsid = op->upcall.req.fsync.refn.fs_id;
			break;
		default:
			break;
		}
	}
	return fsid;
}