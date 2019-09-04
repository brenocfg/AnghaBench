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
struct team_port {int dummy; } ;
struct team {int dummy; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  rx_handler_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  RX_HANDLER_ANOTHER ; 

__attribute__((used)) static rx_handler_result_t team_dummy_receive(struct team *team,
					      struct team_port *port,
					      struct sk_buff *skb)
{
	return RX_HANDLER_ANOTHER;
}