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
struct cosa_data {int dummy; } ;

/* Variables and functions */
 char get_wait_data (struct cosa_data*) ; 
 int put_wait_data (struct cosa_data*,char) ; 
 scalar_t__ puthexnumber (struct cosa_data*,int) ; 

__attribute__((used)) static int startmicrocode(struct cosa_data *cosa, int address)
{
	if (put_wait_data(cosa, 'g') == -1) return -1;
	if (get_wait_data(cosa) != 'g') return -2;
	if (get_wait_data(cosa) != '=') return -3;

	if (puthexnumber(cosa, address) < 0) return -4;
	if (put_wait_data(cosa, '\r') == -1) return -5;
	
	if (get_wait_data(cosa) != '\r') return -6;
	if (get_wait_data(cosa) != '\r') return -7;
	if (get_wait_data(cosa) != '\n') return -8;
	if (get_wait_data(cosa) != '\r') return -9;
	if (get_wait_data(cosa) != '\n') return -10;
#if 0
	printk(KERN_DEBUG "cosa%d: microcode started\n", cosa->num);
#endif
	return 0;
}