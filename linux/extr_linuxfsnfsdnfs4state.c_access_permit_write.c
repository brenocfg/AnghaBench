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
struct nfs4_ol_stateid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_SHARE_ACCESS_BOTH ; 
 int /*<<< orphan*/  NFS4_SHARE_ACCESS_WRITE ; 
 scalar_t__ test_access (int /*<<< orphan*/ ,struct nfs4_ol_stateid*) ; 

__attribute__((used)) static inline int
access_permit_write(struct nfs4_ol_stateid *stp)
{
	return test_access(NFS4_SHARE_ACCESS_WRITE, stp) ||
		test_access(NFS4_SHARE_ACCESS_BOTH, stp);
}