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
typedef  scalar_t__ ptrdiff_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ offset_in_page (char*) ; 
 int scnprintf (char*,scalar_t__,char*,int,unsigned long const*) ; 

int bitmap_print_to_pagebuf(bool list, char *buf, const unsigned long *maskp,
			    int nmaskbits)
{
	ptrdiff_t len = PAGE_SIZE - offset_in_page(buf);

	return list ? scnprintf(buf, len, "%*pbl\n", nmaskbits, maskp) :
		      scnprintf(buf, len, "%*pb\n", nmaskbits, maskp);
}