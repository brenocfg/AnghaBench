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
struct tbnet {int /*<<< orphan*/  dev; int /*<<< orphan*/  handler; } ;
struct tb_service {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 struct tbnet* tb_service_get_drvdata (struct tb_service*) ; 
 int /*<<< orphan*/  tb_unregister_protocol_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tbnet_remove(struct tb_service *svc)
{
	struct tbnet *net = tb_service_get_drvdata(svc);

	unregister_netdev(net->dev);
	tb_unregister_protocol_handler(&net->handler);
	free_netdev(net->dev);
}