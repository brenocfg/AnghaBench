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
struct rocker_port {struct ofdpa_port* wpriv; } ;
struct ofdpa_port {int dummy; } ;
struct neighbour {int /*<<< orphan*/  ha; scalar_t__ primary_key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int OFDPA_OP_FLAG_NOWAIT ; 
 int OFDPA_OP_FLAG_REMOVE ; 
 int ofdpa_port_ipv4_neigh (struct ofdpa_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_neigh_destroy(struct rocker_port *rocker_port,
				    struct neighbour *n)
{
	struct ofdpa_port *ofdpa_port = rocker_port->wpriv;
	int flags = OFDPA_OP_FLAG_REMOVE | OFDPA_OP_FLAG_NOWAIT;
	__be32 ip_addr = *(__be32 *) n->primary_key;

	return ofdpa_port_ipv4_neigh(ofdpa_port, flags, ip_addr, n->ha);
}