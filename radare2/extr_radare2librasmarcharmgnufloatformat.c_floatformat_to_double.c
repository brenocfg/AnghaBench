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
struct floatformat {unsigned int exp_start; int exp_len; unsigned long exp_nan; unsigned int sign_start; int man_len; unsigned int man_start; int exp_bias; scalar_t__ intbit; int /*<<< orphan*/  totalsize; int /*<<< orphan*/  byteorder; } ;

/* Variables and functions */
 double INFINITY ; 
 double NAN ; 
 scalar_t__ floatformat_intbit_no ; 
 long get_field (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 double ldexp (double,long) ; 
 int mant_bits_set (struct floatformat const*,unsigned char const*) ; 
 unsigned int min (int,int) ; 

void
floatformat_to_double (const struct floatformat *fmt,
                       const void *from, double *to)
{
  const unsigned char *ufrom = (const unsigned char *) from;
  double dto;
  long exponent;
  unsigned long mant;
  unsigned int mant_bits, mant_off;
  int mant_bits_left;

  /* Split values are not handled specially, since the top half has
     the correctly rounded double value (in the only supported case of
     split values).  */

  exponent = get_field (ufrom, fmt->byteorder, fmt->totalsize,
			fmt->exp_start, fmt->exp_len);

  /* If the exponent indicates a NaN, we don't have information to
     decide what to do.  So we handle it like IEEE, except that we
     don't try to preserve the type of NaN.  FIXME.  */
  if ((unsigned long) exponent == fmt->exp_nan)
    {
      int nan = mant_bits_set (fmt, ufrom);

      /* On certain systems (such as GNU/Linux), the use of the
	 INFINITY macro below may generate a warning that can not be
	 silenced due to a bug in GCC (PR preprocessor/11931).  The
	 preprocessor fails to recognise the __extension__ keyword in
	 conjunction with the GNU/C99 extension for hexadecimal
	 floating point constants and will issue a warning when
	 compiling with -pedantic.  */
      if (nan) {
	      dto = NAN;
      } else {
	      dto = INFINITY;
      }

      if (get_field (ufrom, fmt->byteorder, fmt->totalsize, fmt->sign_start, 1)) {
	      dto = -dto;
      }

      *to = dto;

      return;
    }

  mant_bits_left = fmt->man_len;
  mant_off = fmt->man_start;
  dto = 0.0;

  /* Build the result algebraically.  Might go infinite, underflow, etc;
     who cares. */

  /* For denorms use minimum exponent.  */
  if (exponent == 0) {
	  exponent = 1 - fmt->exp_bias;
  } else {
	  exponent -= fmt->exp_bias;

	  /* If this format uses a hidden bit, explicitly add it in now.
	 Otherwise, increment the exponent by one to account for the
	 integer bit.  */

	  if (fmt->intbit == floatformat_intbit_no) {
		  dto = ldexp (1.0, exponent);
	  } else {
		  exponent++;
	  }
    }

  while (mant_bits_left > 0)
    {
      mant_bits = min (mant_bits_left, 32);

      mant = get_field (ufrom, fmt->byteorder, fmt->totalsize,
			 mant_off, mant_bits);

      dto += ldexp ((double) mant, exponent - mant_bits);
      exponent -= mant_bits;
      mant_off += mant_bits;
      mant_bits_left -= mant_bits;
    }

  /* Negate it if negative.  */
    if (get_field (ufrom, fmt->byteorder, fmt->totalsize, fmt->sign_start, 1)) {
	    dto = -dto;
    }
    *to = dto;
}