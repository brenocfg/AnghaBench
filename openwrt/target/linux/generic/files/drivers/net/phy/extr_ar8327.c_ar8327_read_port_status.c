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
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int AR8216_PORT_STATUS_LINK_AUTO ; 
 int AR8216_PORT_STATUS_LINK_UP ; 
 int AR8216_PORT_STATUS_RXFLOW ; 
 int AR8216_PORT_STATUS_TXFLOW ; 
 int AR8327_PORT_STATUS_RXFLOW_AUTO ; 
 int AR8327_PORT_STATUS_TXFLOW_AUTO ; 
 int /*<<< orphan*/  AR8327_REG_PORT_STATUS (int) ; 
 int ar8xxx_read (struct ar8xxx_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
ar8327_read_port_status(struct ar8xxx_priv *priv, int port)
{
	u32 t;

	t = ar8xxx_read(priv, AR8327_REG_PORT_STATUS(port));
	/* map the flow control autoneg result bits to the flow control bits
	 * used in forced mode to allow ar8216_read_port_link detect
	 * flow control properly if autoneg is used
	 */
	if (t & AR8216_PORT_STATUS_LINK_UP &&
	    t & AR8216_PORT_STATUS_LINK_AUTO) {
		t &= ~(AR8216_PORT_STATUS_TXFLOW | AR8216_PORT_STATUS_RXFLOW);
		if (t & AR8327_PORT_STATUS_TXFLOW_AUTO)
			t |= AR8216_PORT_STATUS_TXFLOW;
		if (t & AR8327_PORT_STATUS_RXFLOW_AUTO)
			t |= AR8216_PORT_STATUS_RXFLOW;
	}

	return t;
}