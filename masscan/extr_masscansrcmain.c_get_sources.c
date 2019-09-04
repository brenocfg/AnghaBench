#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int first; unsigned int last; } ;
struct TYPE_4__ {unsigned int first; unsigned int last; } ;
struct Source {TYPE_2__ port; TYPE_1__ ip; } ;
struct Masscan {TYPE_3__* nic; } ;
struct TYPE_6__ {struct Source src; } ;

/* Variables and functions */

__attribute__((used)) static void
get_sources(const struct Masscan *masscan,
            unsigned nic_index,
            unsigned *src_ip,
            unsigned *src_ip_mask,
            unsigned *src_port,
            unsigned *src_port_mask)
{
    const struct Source *src = &masscan->nic[nic_index].src;

    *src_ip = src->ip.first;
    *src_ip_mask = src->ip.last - src->ip.first;

    *src_port = src->port.first;
    *src_port_mask = src->port.last - src->port.first;
}