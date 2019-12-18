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
typedef  scalar_t__ tilegx_bundle_bits ;

/* Variables and functions */

__attribute__((used)) static __inline unsigned int
get_Imm8_X0(tilegx_bundle_bits num)
{
  const unsigned int n = (unsigned int)num;
  return (((n >> 12)) & 0xff);
}