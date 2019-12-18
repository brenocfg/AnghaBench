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
 scalar_t__ M_IS_VALID_STATUS (int) ; 
 int socket_active_status ; 

void set_socket_active_status(INT32 Sd, INT32 Status)
{
	if(M_IS_VALID_SD(Sd) && M_IS_VALID_STATUS(Status))
	{
		socket_active_status &= ~(1 << Sd);      /* clean socket's mask */
		socket_active_status |= (Status << Sd); /* set new socket's mask */
	}
}