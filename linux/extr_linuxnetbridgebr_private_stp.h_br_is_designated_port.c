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
struct net_bridge_port {scalar_t__ designated_port; scalar_t__ port_id; TYPE_1__* br; int /*<<< orphan*/  designated_bridge; } ;
struct TYPE_2__ {int /*<<< orphan*/  bridge_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int br_is_designated_port(const struct net_bridge_port *p)
{
	return !memcmp(&p->designated_bridge, &p->br->bridge_id, 8) &&
		(p->designated_port == p->port_id);
}