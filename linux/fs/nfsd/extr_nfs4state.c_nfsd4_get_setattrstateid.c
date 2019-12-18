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
struct TYPE_2__ {int /*<<< orphan*/  sa_stateid; } ;
union nfsd4_op_u {TYPE_1__ setattr; } ;
struct nfsd4_compound_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_stateid (struct nfsd4_compound_state*,int /*<<< orphan*/ *) ; 

void
nfsd4_get_setattrstateid(struct nfsd4_compound_state *cstate,
		union nfsd4_op_u *u)
{
	get_stateid(cstate, &u->setattr.sa_stateid);
}