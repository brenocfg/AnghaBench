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
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 size_t N_ELEMENTS (int /*<<< orphan*/ *) ; 
 scalar_t__ net_contains_ip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reserved_ips ; 

__attribute__((used)) static bool is_reserved_ip(in_addr_t ip)
{
    size_t i;
    for (i = 0; i < N_ELEMENTS(reserved_ips); i++) {
        if (net_contains_ip(&reserved_ips[i], ip))
            return true;
    }
    return false;
}