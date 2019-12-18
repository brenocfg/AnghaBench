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
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  NumericDigit ;

/* Variables and functions */
 int DEC_DIGITS ; 
 scalar_t__ NUMERIC_HDRSZ ; 
 scalar_t__ VARHDRSZ ; 

int32
numeric_maximum_size(int32 typmod)
{
	int			precision;
	int			numeric_digits;

	if (typmod < (int32) (VARHDRSZ))
		return -1;

	/* precision (ie, max # of digits) is in upper bits of typmod */
	precision = ((typmod - VARHDRSZ) >> 16) & 0xffff;

	/*
	 * This formula computes the maximum number of NumericDigits we could need
	 * in order to store the specified number of decimal digits. Because the
	 * weight is stored as a number of NumericDigits rather than a number of
	 * decimal digits, it's possible that the first NumericDigit will contain
	 * only a single decimal digit.  Thus, the first two decimal digits can
	 * require two NumericDigits to store, but it isn't until we reach
	 * DEC_DIGITS + 2 decimal digits that we potentially need a third
	 * NumericDigit.
	 */
	numeric_digits = (precision + 2 * (DEC_DIGITS - 1)) / DEC_DIGITS;

	/*
	 * In most cases, the size of a numeric will be smaller than the value
	 * computed below, because the varlena header will typically get toasted
	 * down to a single byte before being stored on disk, and it may also be
	 * possible to use a short numeric header.  But our job here is to compute
	 * the worst case.
	 */
	return NUMERIC_HDRSZ + (numeric_digits * sizeof(NumericDigit));
}