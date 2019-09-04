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
typedef  size_t rpc_authflavor_t ;

/* Variables and functions */
 size_t RPC_AUTH_MAXFLAVOR ; 
 int /*<<< orphan*/ ** authtab ; 
 int /*<<< orphan*/  authtab_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
svc_auth_unregister(rpc_authflavor_t flavor)
{
	spin_lock(&authtab_lock);
	if (flavor < RPC_AUTH_MAXFLAVOR)
		authtab[flavor] = NULL;
	spin_unlock(&authtab_lock);
}