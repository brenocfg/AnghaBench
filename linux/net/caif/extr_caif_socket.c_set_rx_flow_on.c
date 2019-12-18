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
struct caifsock {int /*<<< orphan*/  flow_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_FLOW_ON_BIT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void set_rx_flow_on(struct caifsock *cf_sk)
{
	 set_bit(RX_FLOW_ON_BIT,
			(void *) &cf_sk->flow_state);
}