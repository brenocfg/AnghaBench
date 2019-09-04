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

/* Variables and functions */
 int USB_PID_DATA0 ; 

__attribute__((used)) static inline u32 dbgp_pid_read_update(u32 x, u32 tok)
{
	return (x & 0xffff0000) | (USB_PID_DATA0 << 8) | (tok & 0xff);
}