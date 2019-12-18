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
 int NET_ID_ZERO ; 
 scalar_t__ net_eq (void*,void*) ; 

__attribute__((used)) static int net_eq_idr(int id, void *net, void *peer)
{
	if (net_eq(net, peer))
		return id ? : NET_ID_ZERO;
	return 0;
}