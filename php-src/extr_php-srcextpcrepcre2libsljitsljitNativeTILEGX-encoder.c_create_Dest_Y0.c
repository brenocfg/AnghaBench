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
typedef  unsigned int const tilegx_bundle_bits ;

/* Variables and functions */

__attribute__((used)) static __inline tilegx_bundle_bits
create_Dest_Y0(int num)
{
  const unsigned int n = (unsigned int)num;
  return ((n & 0x3f) << 0);
}