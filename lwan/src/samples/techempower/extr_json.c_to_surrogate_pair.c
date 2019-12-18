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
typedef  scalar_t__ uint16_t ;
typedef  int uchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void to_surrogate_pair(uchar_t unicode, uint16_t *uc, uint16_t *lc)
{
	uchar_t n;
	
	assert(unicode >= 0x10000 && unicode <= 0x10FFFF);
	
	n = unicode - 0x10000;
	*uc = (uint16_t)(((n >> 10) & 0x3FF) | 0xD800);
	*lc = (uint16_t)((n & 0x3FF) | 0xDC00);
}