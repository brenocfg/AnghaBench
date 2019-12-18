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
typedef  int /*<<< orphan*/  u64 ;
struct ceph_mds_client {int /*<<< orphan*/  oldest_tid; } ;

/* Variables and functions */

__attribute__((used)) static inline  u64 __get_oldest_tid(struct ceph_mds_client *mdsc)
{
	return mdsc->oldest_tid;
}