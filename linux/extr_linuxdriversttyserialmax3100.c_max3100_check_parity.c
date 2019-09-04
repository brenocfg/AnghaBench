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
typedef  int u16 ;
struct max3100_port {int dummy; } ;

/* Variables and functions */
 int max3100_do_parity (struct max3100_port*,int) ; 

__attribute__((used)) static int max3100_check_parity(struct max3100_port *s, u16 c)
{
	return max3100_do_parity(s, c) == ((c >> 8) & 1);
}