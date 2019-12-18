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
typedef  int INT32 ;

/* Variables and functions */
 scalar_t__ M_IS_VALID_SD (int) ; 
 int SOCKET_STATUS_ACTIVE ; 
 int SOCKET_STATUS_INACTIVE ; 
 int socket_active_status ; 

INT32 get_socket_active_status(INT32 Sd)
{
	if(M_IS_VALID_SD(Sd))
	{
		return (socket_active_status & (1 << Sd)) ? SOCKET_STATUS_INACTIVE : SOCKET_STATUS_ACTIVE;
	}
	return SOCKET_STATUS_INACTIVE;
}