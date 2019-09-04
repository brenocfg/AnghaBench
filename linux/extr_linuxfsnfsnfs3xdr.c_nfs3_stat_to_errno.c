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
typedef  enum nfs_stat { ____Placeholder_nfs_stat } nfs_stat ;
struct TYPE_2__ {int stat; int errno; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int) ; 
 TYPE_1__* nfs_errtbl ; 

__attribute__((used)) static int nfs3_stat_to_errno(enum nfs_stat status)
{
	int i;

	for (i = 0; nfs_errtbl[i].stat != -1; i++) {
		if (nfs_errtbl[i].stat == (int)status)
			return nfs_errtbl[i].errno;
	}
	dprintk("NFS: Unrecognized nfs status value: %u\n", status);
	return nfs_errtbl[i].errno;
}