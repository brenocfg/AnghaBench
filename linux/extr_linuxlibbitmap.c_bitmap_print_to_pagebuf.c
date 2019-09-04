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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 char* PTR_ALIGN (char*,int) ; 
 int scnprintf (char*,int,char*,int,unsigned long const*) ; 

int bitmap_print_to_pagebuf(bool list, char *buf, const unsigned long *maskp,
			    int nmaskbits)
{
	ptrdiff_t len = PTR_ALIGN(buf + PAGE_SIZE - 1, PAGE_SIZE) - buf;
	int n = 0;

	if (len > 1)
		n = list ? scnprintf(buf, len, "%*pbl\n", nmaskbits, maskp) :
			   scnprintf(buf, len, "%*pb\n", nmaskbits, maskp);
	return n;
}