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
typedef  int /*<<< orphan*/  png_const_structrp ;
typedef  int* png_charp ;

/* Variables and functions */
 int DBL_DIG ; 
 double DBL_MAX ; 
 double DBL_MIN ; 
 double floor (double) ; 
 int /*<<< orphan*/  frexp (double,int*) ; 
 double modf (double,double*) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 double png_pow10 (int) ; 

void /* PRIVATE */
png_ascii_from_fp(png_const_structrp png_ptr, png_charp ascii, size_t size,
    double fp, unsigned int precision)
{
   /* We use standard functions from math.h, but not printf because
    * that would require stdio.  The caller must supply a buffer of
    * sufficient size or we will png_error.  The tests on size and
    * the space in ascii[] consumed are indicated below.
    */
   if (precision < 1)
      precision = DBL_DIG;

   /* Enforce the limit of the implementation precision too. */
   if (precision > DBL_DIG+1)
      precision = DBL_DIG+1;

   /* Basic sanity checks */
   if (size >= precision+5) /* See the requirements below. */
   {
      if (fp < 0)
      {
         fp = -fp;
         *ascii++ = 45; /* '-'  PLUS 1 TOTAL 1 */
         --size;
      }

      if (fp >= DBL_MIN && fp <= DBL_MAX)
      {
         int exp_b10;   /* A base 10 exponent */
         double base;   /* 10^exp_b10 */

         /* First extract a base 10 exponent of the number,
          * the calculation below rounds down when converting
          * from base 2 to base 10 (multiply by log10(2) -
          * 0.3010, but 77/256 is 0.3008, so exp_b10 needs to
          * be increased.  Note that the arithmetic shift
          * performs a floor() unlike C arithmetic - using a
          * C multiply would break the following for negative
          * exponents.
          */
         (void)frexp(fp, &exp_b10); /* exponent to base 2 */

         exp_b10 = (exp_b10 * 77) >> 8; /* <= exponent to base 10 */

         /* Avoid underflow here. */
         base = png_pow10(exp_b10); /* May underflow */

         while (base < DBL_MIN || base < fp)
         {
            /* And this may overflow. */
            double test = png_pow10(exp_b10+1);

            if (test <= DBL_MAX)
            {
               ++exp_b10; base = test;
            }

            else
               break;
         }

         /* Normalize fp and correct exp_b10, after this fp is in the
          * range [.1,1) and exp_b10 is both the exponent and the digit
          * *before* which the decimal point should be inserted
          * (starting with 0 for the first digit).  Note that this
          * works even if 10^exp_b10 is out of range because of the
          * test on DBL_MAX above.
          */
         fp /= base;
         while (fp >= 1)
         {
            fp /= 10; ++exp_b10;
         }

         /* Because of the code above fp may, at this point, be
          * less than .1, this is ok because the code below can
          * handle the leading zeros this generates, so no attempt
          * is made to correct that here.
          */

         {
            unsigned int czero, clead, cdigits;
            char exponent[10];

            /* Allow up to two leading zeros - this will not lengthen
             * the number compared to using E-n.
             */
            if (exp_b10 < 0 && exp_b10 > -3) /* PLUS 3 TOTAL 4 */
            {
               czero = 0U-exp_b10; /* PLUS 2 digits: TOTAL 3 */
               exp_b10 = 0;      /* Dot added below before first output. */
            }
            else
               czero = 0;    /* No zeros to add */

            /* Generate the digit list, stripping trailing zeros and
             * inserting a '.' before a digit if the exponent is 0.
             */
            clead = czero; /* Count of leading zeros */
            cdigits = 0;   /* Count of digits in list. */

            do
            {
               double d;

               fp *= 10;
               /* Use modf here, not floor and subtract, so that
                * the separation is done in one step.  At the end
                * of the loop don't break the number into parts so
                * that the final digit is rounded.
                */
               if (cdigits+czero+1 < precision+clead)
                  fp = modf(fp, &d);

               else
               {
                  d = floor(fp + .5);

                  if (d > 9)
                  {
                     /* Rounding up to 10, handle that here. */
                     if (czero > 0)
                     {
                        --czero; d = 1;
                        if (cdigits == 0) --clead;
                     }
                     else
                     {
                        while (cdigits > 0 && d > 9)
                        {
                           int ch = *--ascii;

                           if (exp_b10 != (-1))
                              ++exp_b10;

                           else if (ch == 46)
                           {
                              ch = *--ascii; ++size;
                              /* Advance exp_b10 to '1', so that the
                               * decimal point happens after the
                               * previous digit.
                               */
                              exp_b10 = 1;
                           }

                           --cdigits;
                           d = ch - 47;  /* I.e. 1+(ch-48) */
                        }

                        /* Did we reach the beginning? If so adjust the
                         * exponent but take into account the leading
                         * decimal point.
                         */
                        if (d > 9)  /* cdigits == 0 */
                        {
                           if (exp_b10 == (-1))
                           {
                              /* Leading decimal point (plus zeros?), if
                               * we lose the decimal point here it must
                               * be reentered below.
                               */
                              int ch = *--ascii;

                              if (ch == 46)
                              {
                                 ++size; exp_b10 = 1;
                              }

                              /* Else lost a leading zero, so 'exp_b10' is
                               * still ok at (-1)
                               */
                           }
                           else
                              ++exp_b10;

                           /* In all cases we output a '1' */
                           d = 1;
                        }
                     }
                  }
                  fp = 0; /* Guarantees termination below. */
               }

               if (d == 0)
               {
                  ++czero;
                  if (cdigits == 0) ++clead;
               }
               else
               {
                  /* Included embedded zeros in the digit count. */
                  cdigits += czero - clead;
                  clead = 0;

                  while (czero > 0)
                  {
                     /* exp_b10 == (-1) means we just output the decimal
                      * place - after the DP don't adjust 'exp_b10' any
                      * more!
                      */
                     if (exp_b10 != (-1))
                     {
                        if (exp_b10 == 0)
                        {
                           *ascii++ = 46; --size;
                        }
                        /* PLUS 1: TOTAL 4 */
                        --exp_b10;
                     }
                     *ascii++ = 48; --czero;
                  }

                  if (exp_b10 != (-1))
                  {
                     if (exp_b10 == 0)
                     {
                        *ascii++ = 46; --size; /* counted above */
                     }

                     --exp_b10;
                  }
                  *ascii++ = (char)(48 + (int)d); ++cdigits;
               }
            }
            while (cdigits+czero < precision+clead && fp > DBL_MIN);

            /* The total output count (max) is now 4+precision */

            /* Check for an exponent, if we don't need one we are
             * done and just need to terminate the string.  At this
             * point, exp_b10==(-1) is effectively a flag: it got
             * to '-1' because of the decrement, after outputting
             * the decimal point above. (The exponent required is
             * *not* -1.)
             */
            if (exp_b10 >= (-1) && exp_b10 <= 2)
            {
               /* The following only happens if we didn't output the
                * leading zeros above for negative exponent, so this
                * doesn't add to the digit requirement.  Note that the
                * two zeros here can only be output if the two leading
                * zeros were *not* output, so this doesn't increase
                * the output count.
                */
               while (exp_b10-- > 0) *ascii++ = 48;

               *ascii = 0;

               /* Total buffer requirement (including the '\0') is
                * 5+precision - see check at the start.
                */
               return;
            }

            /* Here if an exponent is required, adjust size for
             * the digits we output but did not count.  The total
             * digit output here so far is at most 1+precision - no
             * decimal point and no leading or trailing zeros have
             * been output.
             */
            size -= cdigits;

            *ascii++ = 69; --size;    /* 'E': PLUS 1 TOTAL 2+precision */

            /* The following use of an unsigned temporary avoids ambiguities in
             * the signed arithmetic on exp_b10 and permits GCC at least to do
             * better optimization.
             */
            {
               unsigned int uexp_b10;

               if (exp_b10 < 0)
               {
                  *ascii++ = 45; --size; /* '-': PLUS 1 TOTAL 3+precision */
                  uexp_b10 = 0U-exp_b10;
               }

               else
                  uexp_b10 = 0U+exp_b10;

               cdigits = 0;

               while (uexp_b10 > 0)
               {
                  exponent[cdigits++] = (char)(48 + uexp_b10 % 10);
                  uexp_b10 /= 10;
               }
            }

            /* Need another size check here for the exponent digits, so
             * this need not be considered above.
             */
            if (size > cdigits)
            {
               while (cdigits > 0) *ascii++ = exponent[--cdigits];

               *ascii = 0;

               return;
            }
         }
      }
      else if (!(fp >= DBL_MIN))
      {
         *ascii++ = 48; /* '0' */
         *ascii = 0;
         return;
      }
      else
      {
         *ascii++ = 105; /* 'i' */
         *ascii++ = 110; /* 'n' */
         *ascii++ = 102; /* 'f' */
         *ascii = 0;
         return;
      }
   }

   /* Here on buffer too small. */
   png_error(png_ptr, "ASCII conversion buffer too small");
}