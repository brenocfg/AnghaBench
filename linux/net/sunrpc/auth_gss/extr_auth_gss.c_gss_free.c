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
struct gss_auth {struct gss_auth* target_name; int /*<<< orphan*/  net; int /*<<< orphan*/  mech; int /*<<< orphan*/ * gss_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  gss_mech_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_pipe_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gss_auth*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gss_free(struct gss_auth *gss_auth)
{
	gss_pipe_free(gss_auth->gss_pipe[0]);
	gss_pipe_free(gss_auth->gss_pipe[1]);
	gss_mech_put(gss_auth->mech);
	put_net(gss_auth->net);
	kfree(gss_auth->target_name);

	kfree(gss_auth);
	module_put(THIS_MODULE);
}