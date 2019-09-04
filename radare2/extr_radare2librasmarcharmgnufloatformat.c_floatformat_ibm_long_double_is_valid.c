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
struct floatformat {unsigned int exp_start; int exp_len; unsigned long exp_nan; unsigned int man_len; unsigned int man_start; int /*<<< orphan*/  totalsize; int /*<<< orphan*/  byteorder; struct floatformat* split_half; } ;

/* Variables and functions */
 long get_field (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int mant_bits_set (struct floatformat const*,unsigned char const*) ; 

__attribute__((used)) static int
floatformat_ibm_long_double_is_valid (const struct floatformat *fmt,
				      const void *from)
{
  const unsigned char *ufrom = (const unsigned char *) from;
  const struct floatformat *hfmt = fmt->split_half;
  long top_exp, bot_exp;
  int top_nan = 0;

  top_exp = get_field (ufrom, hfmt->byteorder, hfmt->totalsize,
		       hfmt->exp_start, hfmt->exp_len);
  bot_exp = get_field (ufrom + 8, hfmt->byteorder, hfmt->totalsize,
		       hfmt->exp_start, hfmt->exp_len);

  if ((unsigned long)top_exp == hfmt->exp_nan) {
	  top_nan = mant_bits_set (hfmt, ufrom);
  }

  /* A NaN is valid with any low part.  */
  if (top_nan) {
	  return 1;
  }

  /* An infinity, zero or denormal requires low part 0 (positive or
     negative).  */
  if ((unsigned long) top_exp == hfmt->exp_nan || top_exp == 0)
    {
	  if (bot_exp != 0) {
		  return 0;
	  }

	  return !mant_bits_set (hfmt, ufrom + 8);
    }

  /* The top part is now a finite normal value.  The long double value
     is the sum of the two parts, and the top part must equal the
     result of rounding the long double value to nearest double.  Thus
     the bottom part must be <= 0.5ulp of the top part in absolute
     value, and if it is < 0.5ulp then the long double is definitely
     valid.  */
    if (bot_exp < top_exp - 53) {
	    return 1;
    }
    if (bot_exp > top_exp - 53 && bot_exp != 0) {
	    return 0;
    }
    if (bot_exp == 0) {
	    /* The bottom part is 0 or denormal.  Determine which, and if
	 denormal the first two set bits.  */
	    int first_bit = -1, second_bit = -1, cur_bit;
	    for (cur_bit = 0; (unsigned int)cur_bit < hfmt->man_len; cur_bit++) {
		    if (get_field (ufrom + 8, hfmt->byteorder, hfmt->totalsize,
				hfmt->man_start + cur_bit, 1)) {
			    if (first_bit == -1) {
				    first_bit = cur_bit;
			    } else {
				    second_bit = cur_bit;
				    break;
			    }
		    }
	    }
	    /* Bottom part 0 is OK.  */
	    if (first_bit == -1) {
		    return 1;
	    }
	    /* The real exponent of the bottom part is -first_bit.  */
	    if (-first_bit < top_exp - 53) {
		    return 1;
	    }
	    if (-first_bit > top_exp - 53) {
		    return 0;
	    }
	    /* The bottom part is at least 0.5ulp of the top part.  For this
	 to be OK, the bottom part must be exactly 0.5ulp (i.e. no
	 more bits set) and the top part must have last bit 0.  */
	    if (second_bit != -1) {
		    return 0;
	    }
	    return !get_field (ufrom, hfmt->byteorder, hfmt->totalsize,
		    hfmt->man_start + hfmt->man_len - 1, 1);
    }
  else
    {
      /* The bottom part is at least 0.5ulp of the top part.  For this
	 to be OK, it must be exactly 0.5ulp (i.e. no explicit bits
	 set) and the top part must have last bit 0.  */
      if (get_field (ufrom, hfmt->byteorder, hfmt->totalsize,
		  hfmt->man_start + hfmt->man_len - 1, 1)) {
	      return 0;
      }
      return !mant_bits_set (hfmt, ufrom + 8);
    }
}