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
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_spilib_master_exit (struct gb_connection*) ; 

__attribute__((used)) static void gb_fw_spi_connection_exit(struct gb_connection *connection)
{
	if (!connection)
		return;

	gb_spilib_master_exit(connection);
	gb_connection_disable(connection);
}