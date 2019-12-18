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
typedef  int u32 ;
struct ar8327_port_cfg {int speed; scalar_t__ txpause; scalar_t__ rxpause; scalar_t__ duplex; int /*<<< orphan*/  force_link; } ;

/* Variables and functions */
 int AR8216_PORT_SPEED_1000M ; 
 int AR8216_PORT_SPEED_100M ; 
 int AR8216_PORT_SPEED_10M ; 
 int AR8216_PORT_STATUS_DUPLEX ; 
 int AR8216_PORT_STATUS_LINK_AUTO ; 
 int AR8216_PORT_STATUS_RXFLOW ; 
 int AR8216_PORT_STATUS_RXMAC ; 
 int AR8216_PORT_STATUS_TXFLOW ; 
 int AR8216_PORT_STATUS_TXMAC ; 
#define  AR8327_PORT_SPEED_10 130 
#define  AR8327_PORT_SPEED_100 129 
#define  AR8327_PORT_SPEED_1000 128 

__attribute__((used)) static u32
ar8327_get_port_init_status(struct ar8327_port_cfg *cfg)
{
	u32 t;

	if (!cfg->force_link)
		return AR8216_PORT_STATUS_LINK_AUTO;

	t = AR8216_PORT_STATUS_TXMAC | AR8216_PORT_STATUS_RXMAC;
	t |= cfg->duplex ? AR8216_PORT_STATUS_DUPLEX : 0;
	t |= cfg->rxpause ? AR8216_PORT_STATUS_RXFLOW : 0;
	t |= cfg->txpause ? AR8216_PORT_STATUS_TXFLOW : 0;

	switch (cfg->speed) {
	case AR8327_PORT_SPEED_10:
		t |= AR8216_PORT_SPEED_10M;
		break;
	case AR8327_PORT_SPEED_100:
		t |= AR8216_PORT_SPEED_100M;
		break;
	case AR8327_PORT_SPEED_1000:
		t |= AR8216_PORT_SPEED_1000M;
		break;
	}

	return t;
}