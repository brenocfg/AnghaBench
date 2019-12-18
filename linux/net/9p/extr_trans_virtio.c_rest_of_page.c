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
 unsigned int PAGE_SIZE ; 
 unsigned int offset_in_page (void*) ; 

__attribute__((used)) static unsigned int rest_of_page(void *data)
{
	return PAGE_SIZE - offset_in_page(data);
}