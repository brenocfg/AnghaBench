#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ npy_uint32 ;
typedef  int npy_int32 ;
typedef  double const npy_float64 ;
typedef  int npy_bool ;
struct TYPE_28__ {int length; int* blocks; } ;
typedef  scalar_t__ DigitMode ;
typedef  scalar_t__ CutoffMode ;
typedef  TYPE_1__ BigInt ;

/* Variables and functions */
 int /*<<< orphan*/  BigInt_Add (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ BigInt_Compare (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  BigInt_Copy (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ BigInt_DivideWithRemainder_MaxQuotient9 (TYPE_1__*,TYPE_1__*) ; 
 int BigInt_IsEven (TYPE_1__*) ; 
 scalar_t__ BigInt_IsZero (TYPE_1__*) ; 
 int /*<<< orphan*/  BigInt_Multiply (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  BigInt_Multiply10 (TYPE_1__*) ; 
 int /*<<< orphan*/  BigInt_Multiply2 (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  BigInt_Multiply2_inplace (TYPE_1__*) ; 
 int /*<<< orphan*/  BigInt_MultiplyPow10 (TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  BigInt_Pow10 (TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  BigInt_Pow2 (TYPE_1__*,int const) ; 
 int /*<<< orphan*/  BigInt_Set_uint32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  BigInt_ShiftLeft (TYPE_1__*,int const) ; 
 scalar_t__ const CutoffMode_FractionLength ; 
 scalar_t__ const CutoffMode_TotalLength ; 
 int /*<<< orphan*/  DEBUG_ASSERT (int) ; 
 scalar_t__ const DigitMode_Unique ; 
 scalar_t__ LogBase2_32 (int) ; 
 int NPY_FALSE ; 
 scalar_t__ ceil (double const) ; 

__attribute__((used)) static npy_uint32
Dragon4(BigInt *bigints, const npy_int32 exponent,
        const npy_uint32 mantissaBit, const npy_bool hasUnequalMargins,
        const DigitMode digitMode, const CutoffMode cutoffMode,
        npy_int32 cutoffNumber, char *pOutBuffer,
        npy_uint32 bufferSize, npy_int32 *pOutExponent)
{
    char *curDigit = pOutBuffer;

    /*
     * We compute values in integer format by rescaling as
     *   mantissa = scaledValue / scale
     *   marginLow = scaledMarginLow / scale
     *   marginHigh = scaledMarginHigh / scale
     * Here, marginLow and marginHigh represent 1/2 of the distance to the next
     * floating point value above/below the mantissa.
     *
     * scaledMarginHigh will point to scaledMarginLow in the case they must be
     * equal to each other, otherwise it will point to optionalMarginHigh.
     */
    BigInt *mantissa = &bigints[0];  /* the only initialized bigint */
    BigInt *scale = &bigints[1];
    BigInt *scaledValue = &bigints[2];
    BigInt *scaledMarginLow = &bigints[3];
    BigInt *scaledMarginHigh;
    BigInt *optionalMarginHigh = &bigints[4];

    BigInt *temp1 = &bigints[5];
    BigInt *temp2 = &bigints[6];

    const npy_float64 log10_2 = 0.30102999566398119521373889472449;
    npy_int32 digitExponent, cutoffExponent, hiBlock;
    npy_uint32 outputDigit;    /* current digit being output */
    npy_uint32 outputLen;
    npy_bool isEven = BigInt_IsEven(mantissa);
    npy_int32 cmp;

    /* values used to determine how to round */
    npy_bool low, high, roundDown;

    DEBUG_ASSERT(bufferSize > 0);

    /* if the mantissa is zero, the value is zero regardless of the exponent */
    if (BigInt_IsZero(mantissa)) {
        *curDigit = '0';
        *pOutExponent = 0;
        return 1;
    }

    BigInt_Copy(scaledValue, mantissa);

    if (hasUnequalMargins) {
        /* if we have no fractional component */
        if (exponent > 0) {
            /*
             * 1) Expand the input value by multiplying out the mantissa and
             *    exponent. This represents the input value in its whole number
             *    representation.
             * 2) Apply an additional scale of 2 such that later comparisons
             *    against the margin values are simplified.
             * 3) Set the margin value to the lowest mantissa bit's scale.
             */

            /* scaledValue      = 2 * 2 * mantissa*2^exponent */
            BigInt_ShiftLeft(scaledValue, exponent + 2);
            /* scale            = 2 * 2 * 1 */
            BigInt_Set_uint32(scale,  4);
            /* scaledMarginLow  = 2 * 2^(exponent-1) */
            BigInt_Pow2(scaledMarginLow, exponent);
            /* scaledMarginHigh = 2 * 2 * 2^(exponent-1) */
            BigInt_Pow2(optionalMarginHigh, exponent + 1);
        }
        /* else we have a fractional exponent */
        else {
            /*
             * In order to track the mantissa data as an integer, we store it as
             * is with a large scale
             */

            /* scaledValue      = 2 * 2 * mantissa */
            BigInt_ShiftLeft(scaledValue, 2);
            /* scale            = 2 * 2 * 2^(-exponent) */
            BigInt_Pow2(scale, -exponent + 2);
            /* scaledMarginLow  = 2 * 2^(-1) */
            BigInt_Set_uint32(scaledMarginLow, 1);
            /* scaledMarginHigh = 2 * 2 * 2^(-1) */
            BigInt_Set_uint32(optionalMarginHigh, 2);
        }

        /* the high and low margins are different */
        scaledMarginHigh = optionalMarginHigh;
    }
    else {
        /* if we have no fractional component */
        if (exponent > 0) {
            /* scaledValue     = 2 * mantissa*2^exponent */
            BigInt_ShiftLeft(scaledValue, exponent + 1);
            /* scale           = 2 * 1 */
            BigInt_Set_uint32(scale, 2);
            /* scaledMarginLow = 2 * 2^(exponent-1) */
            BigInt_Pow2(scaledMarginLow, exponent);
        }
        /* else we have a fractional exponent */
        else {
            /*
             * In order to track the mantissa data as an integer, we store it as
             * is with a large scale
             */

            /* scaledValue     = 2 * mantissa */
            BigInt_ShiftLeft(scaledValue, 1);
            /* scale           = 2 * 2^(-exponent) */
            BigInt_Pow2(scale, -exponent + 1);
            /* scaledMarginLow = 2 * 2^(-1) */
            BigInt_Set_uint32(scaledMarginLow, 1);
        }

        /* the high and low margins are equal */
        scaledMarginHigh = scaledMarginLow;
    }

    /*
     * Compute an estimate for digitExponent that will be correct or undershoot
     * by one.  This optimization is based on the paper "Printing Floating-Point
     * Numbers Quickly and Accurately" by Burger and Dybvig
     * http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.72.4656
     * We perform an additional subtraction of 0.69 to increase the frequency of
     * a failed estimate because that lets us take a faster branch in the code.
     * 0.69 is chosen because 0.69 + log10(2) is less than one by a reasonable
     * epsilon that will account for any floating point error.
     *
     * We want to set digitExponent to floor(log10(v)) + 1
     *  v = mantissa*2^exponent
     *  log2(v) = log2(mantissa) + exponent;
     *  log10(v) = log2(v) * log10(2)
     *  floor(log2(v)) = mantissaBit + exponent;
     *  log10(v) - log10(2) < (mantissaBit + exponent) * log10(2) <= log10(v)
     *  log10(v) < (mantissaBit + exponent) * log10(2) + log10(2)
     *                                                 <= log10(v) + log10(2)
     *  floor(log10(v)) < ceil((mantissaBit + exponent) * log10(2))
     *                                                 <= floor(log10(v)) + 1
     *
     *  Warning: This calculation assumes npy_float64 is an IEEE-binary64
     *  float. This line may need to be updated if this is not the case.
     */
    digitExponent = (npy_int32)(
       ceil((npy_float64)((npy_int32)mantissaBit + exponent) * log10_2 - 0.69));

    /*
     * if the digit exponent is smaller than the smallest desired digit for
     * fractional cutoff, pull the digit back into legal range at which point we
     * will round to the appropriate value.  Note that while our value for
     * digitExponent is still an estimate, this is safe because it only
     * increases the number. This will either correct digitExponent to an
     * accurate value or it will clamp it above the accurate value.
     */
    if (cutoffNumber >= 0 && cutoffMode == CutoffMode_FractionLength &&
            digitExponent <= -cutoffNumber) {
        digitExponent = -cutoffNumber + 1;
    }


    /* Divide value by 10^digitExponent. */
    if (digitExponent > 0) {
        /* A positive exponent creates a division so we multiply the scale. */
        BigInt_MultiplyPow10(scale, digitExponent, temp1);
    }
    else if (digitExponent < 0) {
        /*
         * A negative exponent creates a multiplication so we multiply up the
         * scaledValue, scaledMarginLow and scaledMarginHigh.
         */
        BigInt *temp=temp1, *pow10=temp2;
        BigInt_Pow10(pow10, -digitExponent, temp);

        BigInt_Multiply(temp, scaledValue, pow10);
        BigInt_Copy(scaledValue, temp);

        BigInt_Multiply(temp, scaledMarginLow, pow10);
        BigInt_Copy(scaledMarginLow, temp);

        if (scaledMarginHigh != scaledMarginLow) {
            BigInt_Multiply2(scaledMarginHigh, scaledMarginLow);
        }
    }

    /* If (value >= 1), our estimate for digitExponent was too low */
    if (BigInt_Compare(scaledValue, scale) >= 0) {
        /*
         * The exponent estimate was incorrect.
         * Increment the exponent and don't perform the premultiply needed
         * for the first loop iteration.
         */
        digitExponent = digitExponent + 1;
    }
    else {
        /*
         * The exponent estimate was correct.
         * Multiply larger by the output base to prepare for the first loop
         * iteration.
         */
        BigInt_Multiply10(scaledValue);
        BigInt_Multiply10(scaledMarginLow);
        if (scaledMarginHigh != scaledMarginLow) {
            BigInt_Multiply2(scaledMarginHigh, scaledMarginLow);
        }
    }

    /*
     * Compute the cutoff exponent (the exponent of the final digit to print).
     * Default to the maximum size of the output buffer.
     */
    cutoffExponent = digitExponent - bufferSize;
    if (cutoffNumber >= 0) {
        npy_int32 desiredCutoffExponent;

        if (cutoffMode == CutoffMode_TotalLength) {
            desiredCutoffExponent = digitExponent - cutoffNumber;
            if (desiredCutoffExponent > cutoffExponent) {
                cutoffExponent = desiredCutoffExponent;
            }
        }
        /* Otherwise it's CutoffMode_FractionLength. Print cutoffNumber digits
         * past the decimal point or until we reach the buffer size
         */
        else {
            desiredCutoffExponent = -cutoffNumber;
            if (desiredCutoffExponent > cutoffExponent) {
                cutoffExponent = desiredCutoffExponent;
            }
        }
    }

    /* Output the exponent of the first digit we will print */
    *pOutExponent = digitExponent-1;

    /*
     * In preparation for calling BigInt_DivideWithRemainder_MaxQuotient9(), we
     * need to scale up our values such that the highest block of the
     * denominator is greater than or equal to 8. We also need to guarantee that
     * the numerator can never have a length greater than the denominator after
     * each loop iteration.  This requires the highest block of the denominator
     * to be less than or equal to 429496729 which is the highest number that
     * can be multiplied by 10 without overflowing to a new block.
     */
    DEBUG_ASSERT(scale->length > 0);
    hiBlock = scale->blocks[scale->length - 1];
    if (hiBlock < 8 || hiBlock > 429496729) {
        npy_uint32 hiBlockLog2, shift;

        /*
         * Perform a bit shift on all values to get the highest block of the
         * denominator into the range [8,429496729]. We are more likely to make
         * accurate quotient estimations in
         * BigInt_DivideWithRemainder_MaxQuotient9() with higher denominator
         * values so we shift the denominator to place the highest bit at index
         * 27 of the highest block.  This is safe because (2^28 - 1) = 268435455
         * which is less than 429496729. This means that all values with a
         * highest bit at index 27 are within range.
         */
        hiBlockLog2 = LogBase2_32(hiBlock);
        DEBUG_ASSERT(hiBlockLog2 < 3 || hiBlockLog2 > 27);
        shift = (32 + 27 - hiBlockLog2) % 32;

        BigInt_ShiftLeft(scale, shift);
        BigInt_ShiftLeft(scaledValue, shift);
        BigInt_ShiftLeft(scaledMarginLow, shift);
        if (scaledMarginHigh != scaledMarginLow) {
            BigInt_Multiply2(scaledMarginHigh, scaledMarginLow);
        }
    }

    if (digitMode == DigitMode_Unique) {
        /*
         * For the unique cutoff mode, we will try to print until we have
         * reached a level of precision that uniquely distinguishes this value
         * from its neighbors. If we run out of space in the output buffer, we
         * terminate early.
         */
        for (;;) {
            BigInt *scaledValueHigh = temp1;

            digitExponent = digitExponent-1;

            /* divide out the scale to extract the digit */
            outputDigit =
                BigInt_DivideWithRemainder_MaxQuotient9(scaledValue, scale);
            DEBUG_ASSERT(outputDigit < 10);

            /* update the high end of the value */
            BigInt_Add(scaledValueHigh, scaledValue, scaledMarginHigh);

            /*
             * stop looping if we are far enough away from our neighboring
             * values or if we have reached the cutoff digit
             */
            cmp = BigInt_Compare(scaledValue, scaledMarginLow);
            low = isEven ? (cmp <= 0) : (cmp < 0);
            cmp = BigInt_Compare(scaledValueHigh, scale);
            high = isEven ? (cmp >= 0) : (cmp > 0);
            if (low | high | (digitExponent == cutoffExponent))
                break;

            /* store the output digit */
            *curDigit = (char)('0' + outputDigit);
            ++curDigit;

            /* multiply larger by the output base */
            BigInt_Multiply10(scaledValue);
            BigInt_Multiply10(scaledMarginLow);
            if (scaledMarginHigh != scaledMarginLow) {
                BigInt_Multiply2(scaledMarginHigh, scaledMarginLow);
            }
        }
    }
    else {
        /*
         * For exact digit mode, we will try to print until we
         * have exhausted all precision (i.e. all remaining digits are zeros) or
         * until we reach the desired cutoff digit.
         */
        low = NPY_FALSE;
        high = NPY_FALSE;

        for (;;) {
            digitExponent = digitExponent-1;

            /* divide out the scale to extract the digit */
            outputDigit =
                BigInt_DivideWithRemainder_MaxQuotient9(scaledValue, scale);
            DEBUG_ASSERT(outputDigit < 10);

            if ((scaledValue->length == 0) |
                    (digitExponent == cutoffExponent)) {
                break;
            }

            /* store the output digit */
            *curDigit = (char)('0' + outputDigit);
            ++curDigit;

            /* multiply larger by the output base */
            BigInt_Multiply10(scaledValue);
        }
    }

    /* default to rounding down the final digit if value got too close to 0 */
    roundDown = low;

    /* if it is legal to round up and down */
    if (low == high) {
        npy_int32 compare;

        /*
         * round to the closest digit by comparing value with 0.5. To do this we
         * need to convert the inequality to large integer values.
         *  compare( value, 0.5 )
         *  compare( scale * value, scale * 0.5 )
         *  compare( 2 * scale * value, scale )
         */
        BigInt_Multiply2_inplace(scaledValue);
        compare = BigInt_Compare(scaledValue, scale);
        roundDown = compare < 0;

        /*
         * if we are directly in the middle, round towards the even digit (i.e.
         * IEEE rounding rules)
         */
        if (compare == 0) {
            roundDown = (outputDigit & 1) == 0;
        }
    }

    /* print the rounded digit */
    if (roundDown) {
        *curDigit = (char)('0' + outputDigit);
        ++curDigit;
    }
    else {
        /* handle rounding up */
        if (outputDigit == 9) {
            /* find the first non-nine prior digit */
            for (;;) {
                /* if we are at the first digit */
                if (curDigit == pOutBuffer) {
                    /* output 1 at the next highest exponent */
                    *curDigit = '1';
                    ++curDigit;
                    *pOutExponent += 1;
                    break;
                }

                --curDigit;
                if (*curDigit != '9') {
                    /* increment the digit */
                    *curDigit += 1;
                    ++curDigit;
                    break;
                }
            }
        }
        else {
            /* values in the range [0,8] can perform a simple round up */
            *curDigit = (char)('0' + outputDigit + 1);
            ++curDigit;
        }
    }

    /* return the number of digits output */
    outputLen = (npy_uint32)(curDigit - pOutBuffer);
    DEBUG_ASSERT(outputLen <= bufferSize);
    return outputLen;
}