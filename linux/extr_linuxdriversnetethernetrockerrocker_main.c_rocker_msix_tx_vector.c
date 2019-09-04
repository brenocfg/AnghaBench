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
typedef  int /*<<< orphan*/  u32 ;
struct rocker_port {int /*<<< orphan*/  port_number; int /*<<< orphan*/  rocker; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKER_MSIX_VEC_TX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_msix_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 rocker_msix_tx_vector(const struct rocker_port *rocker_port)
{
	return rocker_msix_vector(rocker_port->rocker,
				  ROCKER_MSIX_VEC_TX(rocker_port->port_number));
}