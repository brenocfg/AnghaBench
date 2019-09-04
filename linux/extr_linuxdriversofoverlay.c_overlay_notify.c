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
struct overlay_changeset {int count; struct fragment* fragments; } ;
struct of_overlay_notify_data {int /*<<< orphan*/  target; int /*<<< orphan*/  overlay; } ;
struct fragment {int /*<<< orphan*/  overlay; int /*<<< orphan*/  target; } ;
typedef  enum of_overlay_notify_action { ____Placeholder_of_overlay_notify_action } of_overlay_notify_action ;

/* Variables and functions */
 int NOTIFY_OK ; 
 int NOTIFY_STOP ; 
 int blocking_notifier_call_chain (int /*<<< orphan*/ *,int,struct of_overlay_notify_data*) ; 
 int notifier_to_errno (int) ; 
 int /*<<< orphan*/ * of_overlay_action_name ; 
 int /*<<< orphan*/  overlay_notify_chain ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int overlay_notify(struct overlay_changeset *ovcs,
		enum of_overlay_notify_action action)
{
	struct of_overlay_notify_data nd;
	int i, ret;

	for (i = 0; i < ovcs->count; i++) {
		struct fragment *fragment = &ovcs->fragments[i];

		nd.target = fragment->target;
		nd.overlay = fragment->overlay;

		ret = blocking_notifier_call_chain(&overlay_notify_chain,
						   action, &nd);
		if (ret == NOTIFY_OK || ret == NOTIFY_STOP)
			return 0;
		if (ret) {
			ret = notifier_to_errno(ret);
			pr_err("overlay changeset %s notifier error %d, target: %pOF\n",
			       of_overlay_action_name[action], ret, nd.target);
			return ret;
		}
	}

	return 0;
}