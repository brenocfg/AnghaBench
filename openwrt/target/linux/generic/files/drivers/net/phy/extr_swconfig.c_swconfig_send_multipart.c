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
struct swconfig_callback {scalar_t__ (* fill ) (struct swconfig_callback*,void*) ;scalar_t__ (* close ) (struct swconfig_callback*,void*) ;int /*<<< orphan*/ * msg; struct genl_info* info; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int genlmsg_reply (int /*<<< orphan*/ *,struct genl_info*) ; 
 int /*<<< orphan*/  nlmsg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct swconfig_callback*,void*) ; 
 scalar_t__ stub2 (struct swconfig_callback*,void*) ; 

__attribute__((used)) static int
swconfig_send_multipart(struct swconfig_callback *cb, void *arg)
{
	struct genl_info *info = cb->info;
	int restart = 0;
	int err;

	do {
		if (!cb->msg) {
			cb->msg = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
			if (cb->msg == NULL)
				goto error;
		}

		if (!(cb->fill(cb, arg) < 0))
			break;

		/* fill failed, check if this was already the second attempt */
		if (restart)
			goto error;

		/* try again in a new message, send the current one */
		restart = 1;
		if (cb->close) {
			if (cb->close(cb, arg) < 0)
				goto error;
		}
		err = genlmsg_reply(cb->msg, info);
		cb->msg = NULL;
		if (err < 0)
			goto error;

	} while (restart);

	return 0;

error:
	if (cb->msg)
		nlmsg_free(cb->msg);
	return -1;
}