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
typedef  int ean13 ;

/* Variables and functions */
 scalar_t__ isdigit (unsigned char) ; 

__attribute__((used)) static ean13
str2ean(const char *num)
{
	ean13		ean = 0;		/* current ean */

	while (*num)
	{
		if (isdigit((unsigned char) *num))
			ean = 10 * ean + (*num - '0');
		num++;
	}
	return (ean << 1);			/* also give room to a flag */
}