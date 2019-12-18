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
typedef  int /*<<< orphan*/  socket_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_UNDEFINED ; 
 int /*<<< orphan*/  openvpn_close_socket (int /*<<< orphan*/ ) ; 
 scalar_t__ socket_defined (int /*<<< orphan*/ ) ; 

void
sd_close(socket_descriptor_t *sd)
{
    if (sd && socket_defined(*sd))
    {
        openvpn_close_socket(*sd);
        *sd = SOCKET_UNDEFINED;
    }
}