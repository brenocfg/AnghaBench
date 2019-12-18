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
struct fuse_copy_state {scalar_t__ move_pages; } ;
struct fuse_conn {int dummy; } ;
typedef  enum fuse_notify_code { ____Placeholder_fuse_notify_code } fuse_notify_code ;

/* Variables and functions */
 int EINVAL ; 
#define  FUSE_NOTIFY_DELETE 133 
#define  FUSE_NOTIFY_INVAL_ENTRY 132 
#define  FUSE_NOTIFY_INVAL_INODE 131 
#define  FUSE_NOTIFY_POLL 130 
#define  FUSE_NOTIFY_RETRIEVE 129 
#define  FUSE_NOTIFY_STORE 128 
 int /*<<< orphan*/  fuse_copy_finish (struct fuse_copy_state*) ; 
 int fuse_notify_delete (struct fuse_conn*,unsigned int,struct fuse_copy_state*) ; 
 int fuse_notify_inval_entry (struct fuse_conn*,unsigned int,struct fuse_copy_state*) ; 
 int fuse_notify_inval_inode (struct fuse_conn*,unsigned int,struct fuse_copy_state*) ; 
 int fuse_notify_poll (struct fuse_conn*,unsigned int,struct fuse_copy_state*) ; 
 int fuse_notify_retrieve (struct fuse_conn*,unsigned int,struct fuse_copy_state*) ; 
 int fuse_notify_store (struct fuse_conn*,unsigned int,struct fuse_copy_state*) ; 

__attribute__((used)) static int fuse_notify(struct fuse_conn *fc, enum fuse_notify_code code,
		       unsigned int size, struct fuse_copy_state *cs)
{
	/* Don't try to move pages (yet) */
	cs->move_pages = 0;

	switch (code) {
	case FUSE_NOTIFY_POLL:
		return fuse_notify_poll(fc, size, cs);

	case FUSE_NOTIFY_INVAL_INODE:
		return fuse_notify_inval_inode(fc, size, cs);

	case FUSE_NOTIFY_INVAL_ENTRY:
		return fuse_notify_inval_entry(fc, size, cs);

	case FUSE_NOTIFY_STORE:
		return fuse_notify_store(fc, size, cs);

	case FUSE_NOTIFY_RETRIEVE:
		return fuse_notify_retrieve(fc, size, cs);

	case FUSE_NOTIFY_DELETE:
		return fuse_notify_delete(fc, size, cs);

	default:
		fuse_copy_finish(cs);
		return -EINVAL;
	}
}