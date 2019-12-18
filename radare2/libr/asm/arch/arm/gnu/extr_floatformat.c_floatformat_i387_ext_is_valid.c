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
struct floatformat {int exp_len; int /*<<< orphan*/  man_start; int /*<<< orphan*/  totalsize; int /*<<< orphan*/  byteorder; int /*<<< orphan*/  exp_start; } ;

/* Variables and functions */
 unsigned long get_field (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
floatformat_i387_ext_is_valid (const struct floatformat *fmt, const void *from)
{
  /* In the i387 double-extended format, if the exponent is all ones,
     then the integer bit must be set.  If the exponent is neither 0
     nor ~0, the intbit must also be set.  Only if the exponent is
     zero can it be zero, and then it must be zero.  */
  unsigned long exponent, int_bit;
  const unsigned char *ufrom = (const unsigned char *) from;

  exponent = get_field (ufrom, fmt->byteorder, fmt->totalsize,
			fmt->exp_start, fmt->exp_len);
  int_bit = get_field (ufrom, fmt->byteorder, fmt->totalsize,
		       fmt->man_start, 1);

  if ((exponent == 0) != (int_bit == 0)) {
	  return 0;
  } else {
	  return 1;
  }
}