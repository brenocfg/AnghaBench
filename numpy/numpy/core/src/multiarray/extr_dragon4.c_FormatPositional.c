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
typedef  scalar_t__ npy_uint32 ;
typedef  scalar_t__ npy_int32 ;
typedef  int /*<<< orphan*/  npy_bool ;
typedef  scalar_t__ TrimMode ;
typedef  scalar_t__ DigitMode ;
typedef  scalar_t__ CutoffMode ;
typedef  int /*<<< orphan*/  BigInt ;

/* Variables and functions */
 scalar_t__ CutoffMode_TotalLength ; 
 int /*<<< orphan*/  DEBUG_ASSERT (int) ; 
 scalar_t__ DigitMode_Unique ; 
 scalar_t__ Dragon4 (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,char*,scalar_t__,scalar_t__*) ; 
 scalar_t__ TrimMode_DptZeros ; 
 scalar_t__ TrimMode_LeaveOneZero ; 
 scalar_t__ TrimMode_None ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 

__attribute__((used)) static npy_uint32
FormatPositional(char *buffer, npy_uint32 bufferSize, BigInt *mantissa,
                 npy_int32 exponent, char signbit, npy_uint32 mantissaBit,
                 npy_bool hasUnequalMargins, DigitMode digit_mode,
                 CutoffMode cutoff_mode, npy_int32 precision,
                 TrimMode trim_mode, npy_int32 digits_left,
                 npy_int32 digits_right)
{
    npy_int32 printExponent;
    npy_int32 numDigits, numWholeDigits=0, has_sign=0;

    npy_int32 maxPrintLen = (npy_int32)bufferSize - 1, pos = 0;

    /* track the # of digits past the decimal point that have been printed */
    npy_int32 numFractionDigits = 0, desiredFractionalDigits;

    DEBUG_ASSERT(bufferSize > 0);

    if (digit_mode != DigitMode_Unique) {
        DEBUG_ASSERT(precision >= 0);
    }

    if (signbit == '+' && pos < maxPrintLen) {
        buffer[pos++] = '+';
        has_sign = 1;
    }
    else if (signbit == '-' && pos < maxPrintLen) {
        buffer[pos++] = '-';
        has_sign = 1;
    }

    numDigits = Dragon4(mantissa, exponent, mantissaBit, hasUnequalMargins,
                        digit_mode, cutoff_mode, precision, buffer + has_sign,
                        maxPrintLen - has_sign, &printExponent);

    DEBUG_ASSERT(numDigits > 0);
    DEBUG_ASSERT(numDigits <= bufferSize);

    /* if output has a whole number */
    if (printExponent >= 0) {
        /* leave the whole number at the start of the buffer */
        numWholeDigits = printExponent+1;
        if (numDigits <= numWholeDigits) {
            npy_int32 count = numWholeDigits - numDigits;
            pos += numDigits;

            /* don't overflow the buffer */
            if (pos + count > maxPrintLen) {
                count = maxPrintLen - pos;
            }

            /* add trailing zeros up to the decimal point */
            numDigits += count;
            for ( ; count > 0; count--) {
                buffer[pos++] = '0';
            }
        }
        /* insert the decimal point prior to the fraction */
        else if (numDigits > numWholeDigits) {
            npy_int32 maxFractionDigits;

            numFractionDigits = numDigits - numWholeDigits;
            maxFractionDigits = maxPrintLen - numWholeDigits - 1 - pos;
            if (numFractionDigits > maxFractionDigits) {
                numFractionDigits = maxFractionDigits;
            }

            memmove(buffer + pos + numWholeDigits + 1,
                    buffer + pos + numWholeDigits, numFractionDigits);
            pos += numWholeDigits;
            buffer[pos] = '.';
            numDigits = numWholeDigits + 1 + numFractionDigits;
            pos += 1 + numFractionDigits;
        }
    }
    else {
        /* shift out the fraction to make room for the leading zeros */
        npy_int32 numFractionZeros = 0;
        if (pos + 2 < maxPrintLen) {
            npy_int32 maxFractionZeros, digitsStartIdx, maxFractionDigits, i;

            maxFractionZeros = maxPrintLen - 2 - pos;
            numFractionZeros = -(printExponent + 1);
            if (numFractionZeros > maxFractionZeros) {
                numFractionZeros = maxFractionZeros;
            }

            digitsStartIdx = 2 + numFractionZeros;

            /*
             * shift the significant digits right such that there is room for
             * leading zeros
             */
            numFractionDigits = numDigits;
            maxFractionDigits = maxPrintLen - digitsStartIdx - pos;
            if (numFractionDigits > maxFractionDigits) {
                numFractionDigits = maxFractionDigits;
            }

            memmove(buffer + pos + digitsStartIdx, buffer + pos,
                    numFractionDigits);

            /* insert the leading zeros */
            for (i = 2; i < digitsStartIdx; ++i) {
                buffer[pos + i] = '0';
            }

            /* update the counts */
            numFractionDigits += numFractionZeros;
            numDigits = numFractionDigits;
        }

        /* add the decimal point */
        if (pos + 1 < maxPrintLen) {
            buffer[pos+1] = '.';
        }

        /* add the initial zero */
        if (pos < maxPrintLen) {
            buffer[pos] = '0';
            numDigits += 1;
        }
        numWholeDigits = 1;
        pos += 2 + numFractionDigits;
    }

    /* always add decimal point, except for DprZeros mode */
    if (trim_mode != TrimMode_DptZeros && numFractionDigits == 0 &&
            pos < maxPrintLen) {
        buffer[pos++] = '.';
    }

    desiredFractionalDigits = precision;
    if (cutoff_mode == CutoffMode_TotalLength && precision >= 0) {
        desiredFractionalDigits = precision - numWholeDigits;
    }

    if (trim_mode == TrimMode_LeaveOneZero) {
        /* if we didn't print any fractional digits, add a trailing 0 */
        if (numFractionDigits == 0 && pos < maxPrintLen) {
            buffer[pos++] = '0';
            numFractionDigits++;
        }
    }
    else if (trim_mode == TrimMode_None &&
             digit_mode != DigitMode_Unique &&
             desiredFractionalDigits > numFractionDigits &&
             pos < maxPrintLen) {
        /* add trailing zeros up to precision length */
        /* compute the number of trailing zeros needed */
        npy_int32 count = desiredFractionalDigits - numFractionDigits;
        if (pos + count > maxPrintLen) {
            count = maxPrintLen - pos;
        }
        numFractionDigits += count;

        for ( ; count > 0; count--) {
            buffer[pos++] = '0';
        }
    }
    /* else, for trim_mode Zeros or DptZeros, there is nothing more to add */

    /*
     * when rounding, we may still end up with trailing zeros. Remove them
     * depending on trim settings.
     */
    if (precision >= 0 && trim_mode != TrimMode_None && numFractionDigits > 0) {
        while (buffer[pos-1] == '0') {
            pos--;
            numFractionDigits--;
        }
        if (trim_mode == TrimMode_LeaveOneZero && buffer[pos-1] == '.') {
            buffer[pos++] = '0';
            numFractionDigits++;
        }
    }

    /* add any whitespace padding to right side */
    if (digits_right >= numFractionDigits) {
        npy_int32 count = digits_right - numFractionDigits;

        /* in trim_mode DptZeros, if right padding, add a space for the . */
        if (trim_mode == TrimMode_DptZeros && numFractionDigits == 0
                && pos < maxPrintLen) {
            buffer[pos++] = ' ';
        }

        if (pos + count > maxPrintLen) {
            count = maxPrintLen - pos;
        }

        for ( ; count > 0; count--) {
            buffer[pos++] = ' ';
        }
    }
    /* add any whitespace padding to left side */
    if (digits_left > numWholeDigits + has_sign) {
        npy_int32 shift = digits_left - (numWholeDigits + has_sign);
        npy_int32 count = pos;

        if (count + shift > maxPrintLen) {
            count = maxPrintLen - shift;
        }

        if (count > 0) {
            memmove(buffer + shift, buffer, count);
        }
        pos = shift + count;
        for ( ; shift > 0; shift--) {
            buffer[shift - 1] = ' ';
        }
    }

    /* terminate the buffer */
    DEBUG_ASSERT(pos <= maxPrintLen);
    buffer[pos] = '\0';

    return pos;
}