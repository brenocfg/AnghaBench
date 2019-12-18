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
struct TYPE_2__ {int /*<<< orphan*/  gc_ctx; } ;
struct rpc_gss_data {int /*<<< orphan*/  win; TYPE_1__ gc; int /*<<< orphan*/  ctx; int /*<<< orphan*/  established; } ;
struct authgss_private_data {int /*<<< orphan*/  pd_seq_win; int /*<<< orphan*/  pd_ctx_hndl; int /*<<< orphan*/  pd_ctx; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  log_debug (char*) ; 

bool_t
authgss_get_private_data(AUTH *auth, struct authgss_private_data *pd)
{
	struct rpc_gss_data	*gd;

	log_debug("in authgss_get_private_data()");

	if (!auth || !pd)
		return (FALSE);

	gd = AUTH_PRIVATE(auth);

	if (!gd || !gd->established)
		return (FALSE);

	pd->pd_ctx = gd->ctx;
	pd->pd_ctx_hndl = gd->gc.gc_ctx;
	pd->pd_seq_win = gd->win;

	return (TRUE);
}