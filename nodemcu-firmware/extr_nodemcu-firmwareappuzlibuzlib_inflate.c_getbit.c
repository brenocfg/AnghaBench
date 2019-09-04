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
struct TYPE_3__ {int bitcount; int tag; int (* get_byte ) () ;} ;
typedef  TYPE_1__ UZLIB_DATA ;

/* Variables and functions */
 int stub1 () ; 

__attribute__((used)) static int getbit (UZLIB_DATA *d) {
  uint bit;

  /* check if tag is empty */
  if (!d->bitcount--) {
    /* load next tag */
    d->tag = d->get_byte();
    d->bitcount = 7;
  }

  /* shift bit out of tag */
  bit = d->tag & 0x01;
  d->tag >>= 1;

  return bit;
}