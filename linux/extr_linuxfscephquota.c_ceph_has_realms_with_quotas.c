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
struct ceph_mds_client {int /*<<< orphan*/  quotarealms_count; } ;
struct TYPE_2__ {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* ceph_inode_to_client (struct inode*) ; 

__attribute__((used)) static inline bool ceph_has_realms_with_quotas(struct inode *inode)
{
	struct ceph_mds_client *mdsc = ceph_inode_to_client(inode)->mdsc;
	return atomic64_read(&mdsc->quotarealms_count) > 0;
}