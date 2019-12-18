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
struct gss_api_mech {int /*<<< orphan*/  gm_name; int /*<<< orphan*/  gm_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int gss_mech_svc_setup (struct gss_api_mech*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  registered_mechs ; 
 int /*<<< orphan*/  registered_mechs_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int gss_mech_register(struct gss_api_mech *gm)
{
	int status;

	status = gss_mech_svc_setup(gm);
	if (status)
		return status;
	spin_lock(&registered_mechs_lock);
	list_add_rcu(&gm->gm_list, &registered_mechs);
	spin_unlock(&registered_mechs_lock);
	dprintk("RPC:       registered gss mechanism %s\n", gm->gm_name);
	return 0;
}