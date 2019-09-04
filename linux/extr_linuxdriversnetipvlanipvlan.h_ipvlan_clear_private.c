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
struct ipvl_port {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPVLAN_F_PRIVATE ; 

__attribute__((used)) static inline void ipvlan_clear_private(struct ipvl_port *port)
{
	port->flags &= ~IPVLAN_F_PRIVATE;
}