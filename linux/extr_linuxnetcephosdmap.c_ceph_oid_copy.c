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
struct ceph_object_id {scalar_t__ name_len; int /*<<< orphan*/  name; int /*<<< orphan*/  inline_name; } ;

/* Variables and functions */
 int GFP_NOIO ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  ceph_oid_destroy (struct ceph_object_id*) ; 
 int /*<<< orphan*/  kmalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void ceph_oid_copy(struct ceph_object_id *dest,
		   const struct ceph_object_id *src)
{
	ceph_oid_destroy(dest);

	if (src->name != src->inline_name) {
		/* very rare, see ceph_object_id definition */
		dest->name = kmalloc(src->name_len + 1,
				     GFP_NOIO | __GFP_NOFAIL);
	} else {
		dest->name = dest->inline_name;
	}
	memcpy(dest->name, src->name, src->name_len + 1);
	dest->name_len = src->name_len;
}