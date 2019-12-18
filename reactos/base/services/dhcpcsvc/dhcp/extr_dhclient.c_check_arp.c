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
struct interface_info {int dummy; } ;
struct client_lease {int dummy; } ;

/* Variables and functions */

int check_arp( struct interface_info *ip, struct client_lease *lp ) {
    return 1;
}