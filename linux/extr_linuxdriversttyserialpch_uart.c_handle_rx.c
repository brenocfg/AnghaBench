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
struct eg20t_port {int dummy; } ;

/* Variables and functions */
 int handle_rx_to (struct eg20t_port*) ; 

__attribute__((used)) static int handle_rx(struct eg20t_port *priv)
{
	return handle_rx_to(priv);
}