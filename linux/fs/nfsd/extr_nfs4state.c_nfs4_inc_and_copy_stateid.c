#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ si_generation; } ;
struct nfs4_stid {int /*<<< orphan*/  sc_lock; TYPE_1__ sc_stateid; } ;
typedef  TYPE_1__ stateid_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void
nfs4_inc_and_copy_stateid(stateid_t *dst, struct nfs4_stid *stid)
{
	stateid_t *src = &stid->sc_stateid;

	spin_lock(&stid->sc_lock);
	if (unlikely(++src->si_generation == 0))
		src->si_generation = 1;
	memcpy(dst, src, sizeof(*dst));
	spin_unlock(&stid->sc_lock);
}