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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sc_file; } ;
struct nfs4_ol_stateid {TYPE_1__ st_stid; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_access (int /*<<< orphan*/ ,struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  nfs4_file_put_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_access (int /*<<< orphan*/ ,struct nfs4_ol_stateid*) ; 

__attribute__((used)) static inline void nfs4_stateid_downgrade_bit(struct nfs4_ol_stateid *stp, u32 access)
{
	if (!test_access(access, stp))
		return;
	nfs4_file_put_access(stp->st_stid.sc_file, access);
	clear_access(access, stp);
}