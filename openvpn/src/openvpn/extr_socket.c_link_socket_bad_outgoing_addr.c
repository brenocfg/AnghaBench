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

/* Variables and functions */
 int /*<<< orphan*/  D_READ_WRITE ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*) ; 

void
link_socket_bad_outgoing_addr(void)
{
    dmsg(D_READ_WRITE, "TCP/UDP: No outgoing address to send packet");
}