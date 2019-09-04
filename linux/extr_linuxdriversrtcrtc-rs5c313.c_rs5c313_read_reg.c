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
 unsigned char RS5C313_CNTBIT_AD ; 
 unsigned char RS5C313_CNTBIT_READ ; 
 unsigned char rs5c313_read_data () ; 
 int /*<<< orphan*/  rs5c313_write_data (unsigned char) ; 

__attribute__((used)) static unsigned char rs5c313_read_reg(unsigned char addr)
{

	rs5c313_write_data(addr | RS5C313_CNTBIT_READ | RS5C313_CNTBIT_AD);
	return rs5c313_read_data();
}