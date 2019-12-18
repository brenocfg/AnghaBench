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
 unsigned short CFAG12864B_SIZE ; 
 int* cfag12864b_buffer ; 

__attribute__((used)) static void cfag12864b_fill(void)
{
	unsigned short i;

	for (i = 0; i < CFAG12864B_SIZE; i++)
		cfag12864b_buffer[i] = 0xFF;
}