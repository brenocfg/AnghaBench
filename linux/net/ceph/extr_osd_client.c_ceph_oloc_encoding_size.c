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
struct ceph_object_locator {TYPE_1__* pool_ns; } ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */

__attribute__((used)) static int ceph_oloc_encoding_size(const struct ceph_object_locator *oloc)
{
	return 8 + 4 + 4 + 4 + (oloc->pool_ns ? oloc->pool_ns->len : 0);
}