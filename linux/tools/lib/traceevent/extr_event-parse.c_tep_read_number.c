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
struct tep_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned long long*,void const*,int) ; 
 unsigned long long tep_data2host2 (struct tep_handle*,unsigned short) ; 
 unsigned long long tep_data2host4 (struct tep_handle*,unsigned int) ; 
 unsigned long long tep_data2host8 (struct tep_handle*,unsigned long long) ; 

unsigned long long tep_read_number(struct tep_handle *tep,
				   const void *ptr, int size)
{
	unsigned long long val;

	switch (size) {
	case 1:
		return *(unsigned char *)ptr;
	case 2:
		return tep_data2host2(tep, *(unsigned short *)ptr);
	case 4:
		return tep_data2host4(tep, *(unsigned int *)ptr);
	case 8:
		memcpy(&val, (ptr), sizeof(unsigned long long));
		return tep_data2host8(tep, val);
	default:
		/* BUG! */
		return 0;
	}
}