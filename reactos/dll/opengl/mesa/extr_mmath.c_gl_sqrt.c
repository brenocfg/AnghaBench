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
 float sqrt (float) ; 
 int* sqrttab ; 

float gl_sqrt( float x )
{
#ifdef FAST_MATH
   unsigned int *num = (unsigned int *)&x;
                                /* to access the bits of a float in C
                                 * we must misuse pointers */
                                                        
   short e;                     /* the exponent */
   if (x == 0.0F) return 0.0F;  /* check for square root of 0 */
   e = (*num >> 23) - 127;      /* get the exponent - on a SPARC the */
                                /* exponent is stored with 127 added */
   *num &= 0x7fffff;            /* leave only the mantissa */
   if (e & 0x01) *num |= 0x800000;
                                /* the exponent is odd so we have to */
                                /* look it up in the second half of  */
                                /* the lookup table, so we set the   */
                                /* high bit                                */
   e >>= 1;                     /* divide the exponent by two */
                                /* note that in C the shift */
                                /* operators are sign preserving */
                                /* for signed operands */
   /* Do the table lookup, based on the quaternary mantissa,
    * then reconstruct the result back into a float
    */
   *num = ((sqrttab[*num >> 16]) << 16) | ((e + 127) << 23);
   return x;
#else
   return sqrt(x);
#endif
}