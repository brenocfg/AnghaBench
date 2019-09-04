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
typedef  int tilegx_bundle_bits ;

/* Variables and functions */

__attribute__((used)) static __inline unsigned int
get_ShAmt_Y1(tilegx_bundle_bits n)
{
  return (((unsigned int)(n >> 43)) & 0x3f);
}