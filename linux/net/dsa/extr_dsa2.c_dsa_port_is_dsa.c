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
struct dsa_port {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DSA_PORT_TYPE_DSA ; 

__attribute__((used)) static bool dsa_port_is_dsa(struct dsa_port *port)
{
	return port->type == DSA_PORT_TYPE_DSA;
}