#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct TYPE_3__ {int bitcount; int tag; scalar_t__ (* get_byte ) () ;} ;
typedef  TYPE_1__ UZLIB_DATA ;

/* Variables and functions */
 scalar_t__ stub1 () ; 

__attribute__((used)) static uint read_bits (UZLIB_DATA *d, int num, int base) {
 /* This is an optimised version which doesn't call getbit num times */
  if (!num)
    return base;

  uint i, n = (((uint)-1)<<num);
  for (i = d->bitcount; i < num; i +=8)
    d->tag |= ((uint)d->get_byte()) << i;

  n = d->tag & ~n;
  d->tag >>= num;
  d->bitcount = i - num;
  return base + n;
}