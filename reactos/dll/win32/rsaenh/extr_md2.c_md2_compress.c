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
struct TYPE_3__ {int* X; int* buf; } ;
typedef  TYPE_1__ md2_state ;

/* Variables and functions */
 int* PI_SUBST ; 

__attribute__((used)) static void md2_compress(md2_state *md2)
{
   int j, k;
   unsigned char t;
   
   /* copy block */
   for (j = 0; j < 16; j++) {
       md2->X[16+j] = md2->buf[j];
       md2->X[32+j] = md2->X[j] ^ md2->X[16+j];
   }

   t = 0;

   /* do 18 rounds */
   for (j = 0; j < 18; j++) {
       for (k = 0; k < 48; k++) {
           t = (md2->X[k] ^= PI_SUBST[(int)(t & 255)]);
       }
       t = (t + (unsigned char)j) & 255;
   }
}