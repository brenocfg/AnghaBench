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
struct nfs4_stid {char sc_type; int /*<<< orphan*/  sc_count; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; } ;
typedef  int /*<<< orphan*/  stateid_t ;

/* Variables and functions */
 struct nfs4_stid* find_stateid_locked (struct nfs4_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_stid *
find_stateid_by_type(struct nfs4_client *cl, stateid_t *t, char typemask)
{
	struct nfs4_stid *s;

	spin_lock(&cl->cl_lock);
	s = find_stateid_locked(cl, t);
	if (s != NULL) {
		if (typemask & s->sc_type)
			refcount_inc(&s->sc_count);
		else
			s = NULL;
	}
	spin_unlock(&cl->cl_lock);
	return s;
}