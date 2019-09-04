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
typedef  int ut8 ;
typedef  int ut32 ;

/* Variables and functions */

__attribute__((used)) static inline ut32 be24(ut32 v)
{
	ut32 value = v;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	ut8 * pv = (void *)&v;
	value = (pv[0] << 16) | (pv[1] << 8) | pv[2];
#endif
	return value;
}