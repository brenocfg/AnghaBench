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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ tstbits (int /*<<< orphan*/ *,unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned find_run(__le32 *bmp, unsigned *idx)
{
	unsigned len;
	while (tstbits(bmp, *idx, 1)) {
		(*idx)++;
		if (unlikely(*idx >= 0x4000))
			return 0;
	}
	len = 1;
	while (!tstbits(bmp, *idx + len, 1))
		len++;
	return len;
}