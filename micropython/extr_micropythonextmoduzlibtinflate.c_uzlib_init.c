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

void uzlib_init(void)
{
#ifdef RUNTIME_BITS_TABLES
   /* build extra bits and base tables */
   tinf_build_bits_base(length_bits, length_base, 4, 3);
   tinf_build_bits_base(dist_bits, dist_base, 2, 1);

   /* fix a special case */
   length_bits[28] = 0;
   length_base[28] = 258;
#endif
}