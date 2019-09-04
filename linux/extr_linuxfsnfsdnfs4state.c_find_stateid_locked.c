#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfs4_stid {int /*<<< orphan*/  sc_type; } ;
struct nfs4_client {int /*<<< orphan*/  cl_stateids; } ;
struct TYPE_4__ {int /*<<< orphan*/  so_id; } ;
struct TYPE_5__ {TYPE_1__ si_opaque; } ;
typedef  TYPE_2__ stateid_t ;

/* Variables and functions */
 struct nfs4_stid* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_stid *
find_stateid_locked(struct nfs4_client *cl, stateid_t *t)
{
	struct nfs4_stid *ret;

	ret = idr_find(&cl->cl_stateids, t->si_opaque.so_id);
	if (!ret || !ret->sc_type)
		return NULL;
	return ret;
}