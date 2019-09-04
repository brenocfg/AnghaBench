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
struct rio_mport {int /*<<< orphan*/  phys_rmap; int /*<<< orphan*/  index; scalar_t__ phys_efptr; } ;

/* Variables and functions */
 scalar_t__ RIO_PORT_N_ERR_STS_CSR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RIO_PORT_N_ERR_STS_PORT_OK ; 
 int /*<<< orphan*/  rio_local_read_config_32 (struct rio_mport*,scalar_t__,int*) ; 

__attribute__((used)) static int rio_mport_is_active(struct rio_mport *port)
{
	u32 result = 0;

	rio_local_read_config_32(port,
		port->phys_efptr +
			RIO_PORT_N_ERR_STS_CSR(port->index, port->phys_rmap),
		&result);
	return result & RIO_PORT_N_ERR_STS_PORT_OK;
}