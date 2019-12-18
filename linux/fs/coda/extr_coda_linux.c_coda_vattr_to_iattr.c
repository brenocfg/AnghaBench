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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int u_short ;
struct inode {int i_mode; int i_size; int i_blocks; void* i_ctime; void* i_mtime; void* i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct TYPE_2__ {int tv_sec; } ;
struct coda_vattr {int va_type; int va_mode; int va_uid; int va_gid; int va_nlink; int va_size; TYPE_1__ va_ctime; TYPE_1__ va_mtime; TYPE_1__ va_atime; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
#define  C_VDIR 131 
#define  C_VLNK 130 
#define  C_VNON 129 
#define  C_VREG 128 
 int S_IFDIR ; 
 int S_IFLNK ; 
 int S_IFREG ; 
 void* coda_to_timespec64 (TYPE_1__) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

void coda_vattr_to_iattr(struct inode *inode, struct coda_vattr *attr)
{
        int inode_type;
        /* inode's i_flags, i_ino are set by iget 
           XXX: is this all we need ??
           */
        switch (attr->va_type) {
        case C_VNON:
                inode_type  = 0;
                break;
        case C_VREG:
                inode_type = S_IFREG;
                break;
        case C_VDIR:
                inode_type = S_IFDIR;
                break;
        case C_VLNK:
                inode_type = S_IFLNK;
                break;
        default:
                inode_type = 0;
        }
	inode->i_mode |= inode_type;

	if (attr->va_mode != (u_short) -1)
	        inode->i_mode = attr->va_mode | inode_type;
        if (attr->va_uid != -1) 
	        inode->i_uid = make_kuid(&init_user_ns, (uid_t) attr->va_uid);
        if (attr->va_gid != -1)
	        inode->i_gid = make_kgid(&init_user_ns, (gid_t) attr->va_gid);
	if (attr->va_nlink != -1)
		set_nlink(inode, attr->va_nlink);
	if (attr->va_size != -1)
	        inode->i_size = attr->va_size;
	if (attr->va_size != -1)
		inode->i_blocks = (attr->va_size + 511) >> 9;
	if (attr->va_atime.tv_sec != -1) 
		inode->i_atime = coda_to_timespec64(attr->va_atime);
	if (attr->va_mtime.tv_sec != -1)
		inode->i_mtime = coda_to_timespec64(attr->va_mtime);
        if (attr->va_ctime.tv_sec != -1)
		inode->i_ctime = coda_to_timespec64(attr->va_ctime);
}