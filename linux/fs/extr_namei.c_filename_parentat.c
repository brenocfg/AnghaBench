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
struct qstr {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; } ;
struct nameidata {int last_type; struct qstr last; } ;
struct filename {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INODE_PARENT ; 
 int ECHILD ; 
 struct filename* ERR_PTR (int) ; 
 int ESTALE ; 
 scalar_t__ IS_ERR (struct filename*) ; 
 unsigned int LOOKUP_RCU ; 
 unsigned int LOOKUP_REVAL ; 
 int /*<<< orphan*/  audit_inode (struct filename*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int path_parentat (struct nameidata*,unsigned int,struct path*) ; 
 int /*<<< orphan*/  putname (struct filename*) ; 
 int /*<<< orphan*/  restore_nameidata () ; 
 int /*<<< orphan*/  set_nameidata (struct nameidata*,int,struct filename*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct filename *filename_parentat(int dfd, struct filename *name,
				unsigned int flags, struct path *parent,
				struct qstr *last, int *type)
{
	int retval;
	struct nameidata nd;

	if (IS_ERR(name))
		return name;
	set_nameidata(&nd, dfd, name);
	retval = path_parentat(&nd, flags | LOOKUP_RCU, parent);
	if (unlikely(retval == -ECHILD))
		retval = path_parentat(&nd, flags, parent);
	if (unlikely(retval == -ESTALE))
		retval = path_parentat(&nd, flags | LOOKUP_REVAL, parent);
	if (likely(!retval)) {
		*last = nd.last;
		*type = nd.last_type;
		audit_inode(name, parent->dentry, AUDIT_INODE_PARENT);
	} else {
		putname(name);
		name = ERR_PTR(retval);
	}
	restore_nameidata();
	return name;
}