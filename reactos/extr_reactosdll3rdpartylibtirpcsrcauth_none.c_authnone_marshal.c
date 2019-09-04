#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct authnone_private {int /*<<< orphan*/  mcnt; int /*<<< orphan*/  marshalled_client; } ;
typedef  int /*<<< orphan*/  mutex_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_6__ {TYPE_1__* x_ops; } ;
typedef  TYPE_2__ XDR ;
struct TYPE_5__ {int /*<<< orphan*/  (* x_putbytes ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct authnone_private* authnone_private ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
authnone_marshal(AUTH *client, XDR *xdrs, u_int *seq)
{
	struct authnone_private *ap;
	bool_t dummy;
	extern mutex_t authnone_lock;

	assert(xdrs != NULL);

	ap = authnone_private;
	if (ap == NULL) {
		mutex_unlock(&authnone_lock);
		return (FALSE);
	}
	dummy = (*xdrs->x_ops->x_putbytes)(xdrs,
	    ap->marshalled_client, ap->mcnt);
	mutex_unlock(&authnone_lock);
	return (dummy);
}