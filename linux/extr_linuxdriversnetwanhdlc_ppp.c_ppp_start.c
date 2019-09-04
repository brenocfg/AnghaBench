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
struct proto {int /*<<< orphan*/  pid; int /*<<< orphan*/  state; int /*<<< orphan*/  timer; struct net_device* dev; } ;
struct ppp {struct proto* protos; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSED ; 
 int IDX_COUNT ; 
 size_t IDX_IPCP ; 
 size_t IDX_IPV6CP ; 
 size_t IDX_LCP ; 
 int /*<<< orphan*/  PID_IPCP ; 
 int /*<<< orphan*/  PID_IPV6CP ; 
 int /*<<< orphan*/  PID_LCP ; 
 int /*<<< orphan*/  START ; 
 struct ppp* get_ppp (struct net_device*) ; 
 int /*<<< orphan*/  ppp_cp_event (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppp_timer ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ppp_start(struct net_device *dev)
{
	struct ppp *ppp = get_ppp(dev);
	int i;

	for (i = 0; i < IDX_COUNT; i++) {
		struct proto *proto = &ppp->protos[i];
		proto->dev = dev;
		timer_setup(&proto->timer, ppp_timer, 0);
		proto->state = CLOSED;
	}
	ppp->protos[IDX_LCP].pid = PID_LCP;
	ppp->protos[IDX_IPCP].pid = PID_IPCP;
	ppp->protos[IDX_IPV6CP].pid = PID_IPV6CP;

	ppp_cp_event(dev, PID_LCP, START, 0, 0, 0, NULL);
}