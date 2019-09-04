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

/* Variables and functions */
 int VHOST_NET_PKT_WEIGHT ; 
 int VHOST_NET_WEIGHT ; 

__attribute__((used)) static bool vhost_exceeds_weight(int pkts, int total_len)
{
	return total_len >= VHOST_NET_WEIGHT ||
	       pkts >= VHOST_NET_PKT_WEIGHT;
}