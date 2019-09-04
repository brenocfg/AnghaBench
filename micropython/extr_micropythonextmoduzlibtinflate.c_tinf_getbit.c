#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bitcount; int tag; } ;
typedef  TYPE_1__ TINF_DATA ;

/* Variables and functions */
 int uzlib_get_byte (TYPE_1__*) ; 

__attribute__((used)) static int tinf_getbit(TINF_DATA *d)
{
   unsigned int bit;

   /* check if tag is empty */
   if (!d->bitcount--)
   {
      /* load next tag */
      d->tag = uzlib_get_byte(d);
      d->bitcount = 7;
   }

   /* shift bit out of tag */
   bit = d->tag & 0x01;
   d->tag >>= 1;

   return bit;
}