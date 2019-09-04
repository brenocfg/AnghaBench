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
struct zfcp_port {int dummy; } ;

/* Variables and functions */
 int ZFCP_STATUS_COMMON_UNBLOCKED ; 
 int /*<<< orphan*/  zfcp_erp_clear_port_status (struct zfcp_port*,int) ; 

__attribute__((used)) static void zfcp_erp_port_block(struct zfcp_port *port, int clear)
{
	zfcp_erp_clear_port_status(port,
				    ZFCP_STATUS_COMMON_UNBLOCKED | clear);
}