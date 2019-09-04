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
typedef  int npy_uint32 ;
typedef  scalar_t__ npy_int32 ;
typedef  int /*<<< orphan*/  npy_bool ;
typedef  scalar_t__ TrimMode ;
typedef  scalar_t__ DigitMode ;
typedef  int /*<<< orphan*/  BigInt ;

/* Variables and functions */
 int /*<<< orphan*/  CutoffMode_TotalLength ; 
 int /*<<< orphan*/  DEBUG_ASSERT (int) ; 
 scalar_t__ DigitMode_Unique ; 
 scalar_t__ Dragon4 (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,char*,int,scalar_t__*) ; 
 scalar_t__ TrimMode_DptZeros ; 
 scalar_t__ TrimMode_LeaveOneZero ; 
 scalar_t__ TrimMode_None ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 

__attribute__((used)) static npy_uint32
FormatScientific (char *buffer, npy_uint32 bufferSize, BigInt *mantissa,
                  npy_int32 exponent, char signbit, npy_uint32 mantissaBit,
                  npy_bool hasUnequalMargins, DigitMode digit_mode,
                  npy_int32 precision, TrimMode trim_mode,
                  npy_int32 digits_left, npy_int32 exp_digits)
{
    npy_int32 printExponent;
    npy_int32 numDigits;
    char *pCurOut;
    npy_int32 numFractionDigits;
    npy_int32 leftchars;

    if (digit_mode != DigitMode_Unique) {
        DEBUG_ASSERT(precision >= 0);
    }


    DEBUG_ASSERT(bufferSize > 0);

    pCurOut = buffer;

    /* add any whitespace padding to left side */
    leftchars = 1 + (signbit == '-' || signbit == '+');
    if (digits_left > leftchars) {
        int i;
        for (i = 0; i < digits_left - leftchars && bufferSize > 1; i++) {
            *pCurOut = ' ';
            pCurOut++;
            --bufferSize;
        }
    }

    if (signbit == '+' && bufferSize > 1) {
        *pCurOut = '+';
        pCurOut++;
        --bufferSize;
    }
    else if (signbit == '-'  && bufferSize > 1) {
        *pCurOut = '-';
        pCurOut++;
        --bufferSize;
    }

    numDigits = Dragon4(mantissa, exponent, mantissaBit, hasUnequalMargins,
                        digit_mode, CutoffMode_TotalLength, precision + 1,
                        pCurOut, bufferSize, &printExponent);

    DEBUG_ASSERT(numDigits > 0);
    DEBUG_ASSERT(numDigits <= bufferSize);

    /* keep the whole number as the first digit */
    if (bufferSize > 1) {
        pCurOut += 1;
        bufferSize -= 1;
    }

    /* insert the decimal point prior to the fractional number */
    numFractionDigits = numDigits-1;
    if (numFractionDigits > 0 && bufferSize > 1) {
        npy_int32 maxFractionDigits = (npy_int32)bufferSize - 2;

        if (numFractionDigits > maxFractionDigits) {
            numFractionDigits =  maxFractionDigits;
        }

        memmove(pCurOut + 1, pCurOut, numFractionDigits);
        pCurOut[0] = '.';
        pCurOut += (1 + numFractionDigits);
        bufferSize -= (1 + numFractionDigits);
    }

    /* always add decimal point, except for DprZeros mode */
    if (trim_mode != TrimMode_DptZeros && numFractionDigits == 0 &&
            bufferSize > 1) {
        *pCurOut = '.';
        ++pCurOut;
        --bufferSize;
    }

    if (trim_mode == TrimMode_LeaveOneZero) {
        /* if we didn't print any fractional digits, add the 0 */
        if (numFractionDigits == 0 && bufferSize > 1) {
            *pCurOut = '0';
            ++pCurOut;
            --bufferSize;
            ++numFractionDigits;
        }
    }
    else if (trim_mode == TrimMode_None &&
            digit_mode != DigitMode_Unique) {
        /* add trailing zeros up to precision length */
        if (precision > (npy_int32)numFractionDigits) {
            char *pEnd;
            /* compute the number of trailing zeros needed */
            npy_int32 numZeros = (precision - numFractionDigits);

            if (numZeros > (npy_int32)bufferSize - 1) {
                numZeros = (npy_int32)bufferSize - 1;
            }

            for (pEnd = pCurOut + numZeros; pCurOut < pEnd; ++pCurOut) {
                *pCurOut = '0';
                ++numFractionDigits;
            }
        }
    }
    /* else, for trim_mode Zeros or DptZeros, there is nothing more to add */

    /*
     * when rounding, we may still end up with trailing zeros. Remove them
     * depending on trim settings.
     */
    if (precision >= 0 && trim_mode != TrimMode_None && numFractionDigits > 0) {
        --pCurOut;
        while (*pCurOut == '0') {
            --pCurOut;
            ++bufferSize;
            --numFractionDigits;
        }
        if (trim_mode == TrimMode_LeaveOneZero && *pCurOut == '.') {
            ++pCurOut;
            *pCurOut = '0';
            --bufferSize;
            ++numFractionDigits;
        }
        ++pCurOut;
    }

    /* print the exponent into a local buffer and copy into output buffer */
    if (bufferSize > 1) {
        char exponentBuffer[7];
        npy_int32 digits[5];
        npy_int32 i, exp_size, count;

        if (exp_digits > 5) {
            exp_digits = 5;
        }
        if (exp_digits < 0) {
            exp_digits = 2;
        }

        exponentBuffer[0] = 'e';
        if (printExponent >= 0) {
            exponentBuffer[1] = '+';
        }
        else {
            exponentBuffer[1] = '-';
            printExponent = -printExponent;
        }

        DEBUG_ASSERT(printExponent < 100000);

        /* get exp digits */
        for (i = 0; i < 5; i++) {
            digits[i] = printExponent % 10;
            printExponent /= 10;
        }
        /* count back over leading zeros */
        for (i = 5; i > exp_digits && digits[i-1] == 0; i--) {
        }
        exp_size = i;
        /* write remaining digits to tmp buf */
        for (i = exp_size; i > 0; i--) {
            exponentBuffer[2 + (exp_size-i)] = (char)('0' + digits[i-1]);
        }

        /* copy the exponent buffer into the output */
        count = exp_size + 2;
        if (count > (npy_int32)bufferSize - 1) {
            count = (npy_int32)bufferSize - 1;
        }
        memcpy(pCurOut, exponentBuffer, count);
        pCurOut += count;
        bufferSize -= count;
    }


    DEBUG_ASSERT(bufferSize > 0);
    pCurOut[0] = '\0';

    return pCurOut - buffer;
}