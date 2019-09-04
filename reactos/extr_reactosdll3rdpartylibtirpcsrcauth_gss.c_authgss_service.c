#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int gc_svc; } ;
struct TYPE_3__ {int svc; } ;
struct rpc_gss_data {TYPE_2__ gc; TYPE_1__ sec; int /*<<< orphan*/  established; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  log_debug (char*) ; 

bool_t
authgss_service(AUTH *auth, int svc)
{
	struct rpc_gss_data	*gd;

	log_debug("in authgss_service()");

	if (!auth)
		return(FALSE);
	gd = AUTH_PRIVATE(auth);
	if (!gd || !gd->established)
		return (FALSE);
	gd->sec.svc = svc;
	gd->gc.gc_svc = svc;
	return (TRUE);
}