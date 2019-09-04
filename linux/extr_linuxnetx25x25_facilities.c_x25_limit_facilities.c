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
struct x25_neigh {int /*<<< orphan*/  extended; } ;
struct x25_facilities {int winsize_in; int winsize_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 

void x25_limit_facilities(struct x25_facilities *facilities,
			  struct x25_neigh *nb)
{

	if (!nb->extended) {
		if (facilities->winsize_in  > 7) {
			pr_debug("incoming winsize limited to 7\n");
			facilities->winsize_in = 7;
		}
		if (facilities->winsize_out > 7) {
			facilities->winsize_out = 7;
			pr_debug("outgoing winsize limited to 7\n");
		}
	}
}