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
struct TYPE_2__ {int /*<<< orphan*/  od_stateid; } ;
union nfsd4_op_u {TYPE_1__ open_downgrade; } ;
struct nfsd4_compound_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_stateid (struct nfsd4_compound_state*,int /*<<< orphan*/ *) ; 

void
nfsd4_set_opendowngradestateid(struct nfsd4_compound_state *cstate,
		union nfsd4_op_u *u)
{
	put_stateid(cstate, &u->open_downgrade.od_stateid);
}