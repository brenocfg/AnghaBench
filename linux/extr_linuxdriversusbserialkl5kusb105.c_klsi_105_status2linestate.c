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
typedef  int __u16 ;

/* Variables and functions */
 int const KL5KUSB105A_CTS ; 
 int const KL5KUSB105A_DSR ; 
 unsigned long TIOCM_CTS ; 
 unsigned long TIOCM_DSR ; 

__attribute__((used)) static unsigned long klsi_105_status2linestate(const __u16 status)
{
	unsigned long res = 0;

	res =   ((status & KL5KUSB105A_DSR) ? TIOCM_DSR : 0)
	      | ((status & KL5KUSB105A_CTS) ? TIOCM_CTS : 0)
	      ;

	return res;
}