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
struct rocker_port {TYPE_1__* dev; } ;
struct TYPE_2__ {size_t mtu; } ;

/* Variables and functions */
 size_t ETH_FCS_LEN ; 
 size_t ETH_HLEN ; 
 size_t VLAN_HLEN ; 

__attribute__((used)) static size_t rocker_port_rx_buf_len(const struct rocker_port *rocker_port)
{
	return rocker_port->dev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
}