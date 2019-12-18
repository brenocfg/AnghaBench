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
typedef  int /*<<< orphan*/  npy_uint32 ;
typedef  int /*<<< orphan*/  npy_int32 ;
typedef  int /*<<< orphan*/  npy_bool ;
struct TYPE_3__ {int /*<<< orphan*/  digits_right; int /*<<< orphan*/  digits_left; int /*<<< orphan*/  trim_mode; int /*<<< orphan*/  precision; int /*<<< orphan*/  cutoff_mode; int /*<<< orphan*/  digit_mode; int /*<<< orphan*/  exp_digits; scalar_t__ scientific; } ;
typedef  TYPE_1__ Dragon4_Options ;
typedef  int /*<<< orphan*/  BigInt ;

/* Variables and functions */
 int /*<<< orphan*/  FormatPositional (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FormatScientific (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static npy_uint32
Format_floatbits(char *buffer, npy_uint32 bufferSize, BigInt *mantissa,
                 npy_int32 exponent, char signbit, npy_uint32 mantissaBit,
                 npy_bool hasUnequalMargins, Dragon4_Options *opt)
{
    /* format the value */
    if (opt->scientific) {
        return FormatScientific(buffer, bufferSize, mantissa, exponent,
                                signbit, mantissaBit, hasUnequalMargins,
                                opt->digit_mode, opt->precision,
                                opt->trim_mode, opt->digits_left,
                                opt->exp_digits);
    }
    else {
        return FormatPositional(buffer, bufferSize, mantissa, exponent,
                                signbit, mantissaBit, hasUnequalMargins,
                                opt->digit_mode, opt->cutoff_mode,
                                opt->precision, opt->trim_mode,
                                opt->digits_left, opt->digits_right);
    }
}