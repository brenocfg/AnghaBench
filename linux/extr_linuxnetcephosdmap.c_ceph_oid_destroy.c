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
struct ceph_object_id {scalar_t__ name; scalar_t__ inline_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__) ; 

void ceph_oid_destroy(struct ceph_object_id *oid)
{
	if (oid->name != oid->inline_name)
		kfree(oid->name);
}