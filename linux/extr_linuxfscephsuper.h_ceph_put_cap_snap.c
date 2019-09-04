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
struct ceph_cap_snap {scalar_t__ xattr_blob; int /*<<< orphan*/  nref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_buffer_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ceph_cap_snap*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ceph_put_cap_snap(struct ceph_cap_snap *capsnap)
{
	if (refcount_dec_and_test(&capsnap->nref)) {
		if (capsnap->xattr_blob)
			ceph_buffer_put(capsnap->xattr_blob);
		kfree(capsnap);
	}
}