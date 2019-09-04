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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  cifsAttrs; } ;

/* Variables and functions */
 TYPE_1__* CIFS_I (struct inode*) ; 
 int ERANGE ; 
 int cifs_revalidate_dentry_attr (struct dentry*) ; 

__attribute__((used)) static int cifs_attrib_get(struct dentry *dentry,
			   struct inode *inode, void *value,
			   size_t size)
{
	ssize_t rc;
	__u32 *pattribute;

	rc = cifs_revalidate_dentry_attr(dentry);

	if (rc)
		return rc;

	if ((value == NULL) || (size == 0))
		return sizeof(__u32);
	else if (size < sizeof(__u32))
		return -ERANGE;

	/* return dos attributes as pseudo xattr */
	pattribute = (__u32 *)value;
	*pattribute = CIFS_I(inode)->cifsAttrs;

	return sizeof(__u32);
}