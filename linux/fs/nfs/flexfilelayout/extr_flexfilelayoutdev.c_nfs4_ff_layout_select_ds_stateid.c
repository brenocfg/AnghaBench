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
struct nfs4_ff_layout_mirror {int /*<<< orphan*/  stateid; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int nfs4_ff_layout_ds_version (struct nfs4_ff_layout_mirror const*) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nfs4_ff_layout_select_ds_stateid(const struct nfs4_ff_layout_mirror *mirror,
		nfs4_stateid *stateid)
{
	if (nfs4_ff_layout_ds_version(mirror) == 4)
		nfs4_stateid_copy(stateid, &mirror->stateid);
}