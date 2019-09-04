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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct port100_sync_cmd_response {struct sk_buff* resp; int /*<<< orphan*/  done; } ;
struct port100 {int dummy; } ;

/* Variables and functions */
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int port100_send_cmd_async (struct port100*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,struct port100_sync_cmd_response*) ; 
 int /*<<< orphan*/  port100_send_sync_complete ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *port100_send_cmd_sync(struct port100 *dev, u8 cmd_code,
					     struct sk_buff *req)
{
	int rc;
	struct port100_sync_cmd_response arg;

	init_completion(&arg.done);

	rc = port100_send_cmd_async(dev, cmd_code, req,
				    port100_send_sync_complete, &arg);
	if (rc) {
		dev_kfree_skb(req);
		return ERR_PTR(rc);
	}

	wait_for_completion(&arg.done);

	return arg.resp;
}