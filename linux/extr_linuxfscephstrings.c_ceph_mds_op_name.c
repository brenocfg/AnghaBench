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

/* Variables and functions */
#define  CEPH_MDS_OP_CREATE 155 
#define  CEPH_MDS_OP_GETATTR 154 
#define  CEPH_MDS_OP_GETFILELOCK 153 
#define  CEPH_MDS_OP_LINK 152 
#define  CEPH_MDS_OP_LOOKUP 151 
#define  CEPH_MDS_OP_LOOKUPHASH 150 
#define  CEPH_MDS_OP_LOOKUPINO 149 
#define  CEPH_MDS_OP_LOOKUPNAME 148 
#define  CEPH_MDS_OP_LOOKUPPARENT 147 
#define  CEPH_MDS_OP_LOOKUPSNAP 146 
#define  CEPH_MDS_OP_LSSNAP 145 
#define  CEPH_MDS_OP_MKDIR 144 
#define  CEPH_MDS_OP_MKNOD 143 
#define  CEPH_MDS_OP_MKSNAP 142 
#define  CEPH_MDS_OP_OPEN 141 
#define  CEPH_MDS_OP_READDIR 140 
#define  CEPH_MDS_OP_RENAME 139 
#define  CEPH_MDS_OP_RENAMESNAP 138 
#define  CEPH_MDS_OP_RMDIR 137 
#define  CEPH_MDS_OP_RMSNAP 136 
#define  CEPH_MDS_OP_RMXATTR 135 
#define  CEPH_MDS_OP_SETATTR 134 
#define  CEPH_MDS_OP_SETDIRLAYOUT 133 
#define  CEPH_MDS_OP_SETFILELOCK 132 
#define  CEPH_MDS_OP_SETLAYOUT 131 
#define  CEPH_MDS_OP_SETXATTR 130 
#define  CEPH_MDS_OP_SYMLINK 129 
#define  CEPH_MDS_OP_UNLINK 128 

const char *ceph_mds_op_name(int op)
{
	switch (op) {
	case CEPH_MDS_OP_LOOKUP:  return "lookup";
	case CEPH_MDS_OP_LOOKUPHASH:  return "lookuphash";
	case CEPH_MDS_OP_LOOKUPPARENT:  return "lookupparent";
	case CEPH_MDS_OP_LOOKUPINO:  return "lookupino";
	case CEPH_MDS_OP_LOOKUPNAME:  return "lookupname";
	case CEPH_MDS_OP_GETATTR:  return "getattr";
	case CEPH_MDS_OP_SETXATTR: return "setxattr";
	case CEPH_MDS_OP_SETATTR: return "setattr";
	case CEPH_MDS_OP_RMXATTR: return "rmxattr";
	case CEPH_MDS_OP_SETLAYOUT: return "setlayou";
	case CEPH_MDS_OP_SETDIRLAYOUT: return "setdirlayout";
	case CEPH_MDS_OP_READDIR: return "readdir";
	case CEPH_MDS_OP_MKNOD: return "mknod";
	case CEPH_MDS_OP_LINK: return "link";
	case CEPH_MDS_OP_UNLINK: return "unlink";
	case CEPH_MDS_OP_RENAME: return "rename";
	case CEPH_MDS_OP_MKDIR: return "mkdir";
	case CEPH_MDS_OP_RMDIR: return "rmdir";
	case CEPH_MDS_OP_SYMLINK: return "symlink";
	case CEPH_MDS_OP_CREATE: return "create";
	case CEPH_MDS_OP_OPEN: return "open";
	case CEPH_MDS_OP_LOOKUPSNAP: return "lookupsnap";
	case CEPH_MDS_OP_LSSNAP: return "lssnap";
	case CEPH_MDS_OP_MKSNAP: return "mksnap";
	case CEPH_MDS_OP_RMSNAP: return "rmsnap";
	case CEPH_MDS_OP_RENAMESNAP: return "renamesnap";
	case CEPH_MDS_OP_SETFILELOCK: return "setfilelock";
	case CEPH_MDS_OP_GETFILELOCK: return "getfilelock";
	}
	return "???";
}