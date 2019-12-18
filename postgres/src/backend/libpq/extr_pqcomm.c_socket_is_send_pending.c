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
 scalar_t__ PqSendPointer ; 
 scalar_t__ PqSendStart ; 

__attribute__((used)) static bool
socket_is_send_pending(void)
{
	return (PqSendStart < PqSendPointer);
}