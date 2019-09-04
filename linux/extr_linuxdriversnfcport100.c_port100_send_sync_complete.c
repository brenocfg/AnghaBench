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
struct sk_buff {int dummy; } ;
struct port100_sync_cmd_response {int /*<<< orphan*/  done; struct sk_buff* resp; } ;
struct port100 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void port100_send_sync_complete(struct port100 *dev, void *_arg,
				      struct sk_buff *resp)
{
	struct port100_sync_cmd_response *arg = _arg;

	arg->resp = resp;
	complete(&arg->done);
}