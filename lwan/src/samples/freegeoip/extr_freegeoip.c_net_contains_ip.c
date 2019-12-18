#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union ip_to_octet {int* octet; int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {int* octet; } ;
struct TYPE_3__ {int* octet; } ;
struct ip_net {TYPE_2__ mask; TYPE_1__ ip; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */

__attribute__((used)) static bool net_contains_ip(const struct ip_net *net, in_addr_t ip)
{
    union ip_to_octet _ip = {.ip = ip};
    return (net->ip.octet[0] & net->mask.octet[0]) ==
               (_ip.octet[0] & net->mask.octet[0]) &&
           (net->ip.octet[1] & net->mask.octet[1]) ==
               (_ip.octet[1] & net->mask.octet[1]) &&
           (net->ip.octet[2] & net->mask.octet[2]) ==
               (_ip.octet[2] & net->mask.octet[2]) &&
           (net->ip.octet[3] & net->mask.octet[3]) ==
               (_ip.octet[3] & net->mask.octet[3]);
}