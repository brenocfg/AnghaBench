#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_uint32 ;
typedef  int npy_int32 ;
typedef  int /*<<< orphan*/  npy_float32 ;
typedef  int npy_bool ;
struct TYPE_7__ {scalar_t__ sign; } ;
struct TYPE_6__ {char* repr; int /*<<< orphan*/ * bigints; } ;
typedef  TYPE_1__ Dragon4_Scratch ;
typedef  TYPE_2__ Dragon4_Options ;
typedef  int /*<<< orphan*/  BigInt ;

/* Variables and functions */
 int /*<<< orphan*/  BigInt_Set_uint32 (int /*<<< orphan*/ *,int) ; 
 int Format_floatbits (char*,int,int /*<<< orphan*/ *,int,char,int,int,TYPE_2__*) ; 
 int LogBase2_32 (int) ; 
 int NPY_FALSE ; 
 int PrintInfNan (char*,int,int,int,char) ; 
 int bitmask_u32 (int) ; 

__attribute__((used)) static npy_uint32
Dragon4_PrintFloat_IEEE_binary32(
        Dragon4_Scratch *scratch, npy_float32 *value,
        Dragon4_Options *opt)
{
    char *buffer = scratch->repr;
    npy_uint32 bufferSize = sizeof(scratch->repr);
    BigInt *bigints = scratch->bigints;

    union
    {
        npy_float32 floatingPoint;
        npy_uint32 integer;
    } floatUnion;
    npy_uint32 floatExponent, floatMantissa, floatSign;

    npy_uint32 mantissa;
    npy_int32 exponent;
    npy_uint32 mantissaBit;
    npy_bool hasUnequalMargins;
    char signbit = '\0';

    if (bufferSize == 0) {
        return 0;
    }

    if (bufferSize == 1) {
        buffer[0] = '\0';
        return 0;
    }

    /* deconstruct the floating point value */
    floatUnion.floatingPoint = *value;
    floatMantissa = floatUnion.integer & bitmask_u32(23);
    floatExponent = (floatUnion.integer >> 23) & bitmask_u32(8);
    floatSign = floatUnion.integer >> 31;

    /* output the sign */
    if (floatSign != 0) {
        signbit = '-';
    }
    else if (opt->sign) {
        signbit = '+';
    }

    /* if this is a special value */
    if (floatExponent == bitmask_u32(8)) {
        return PrintInfNan(buffer, bufferSize, floatMantissa, 6, signbit);
    }
    /* else this is a number */

    /* factor the value into its parts */
    if (floatExponent != 0) {
        /*
         * normalized
         * The floating point equation is:
         *  value = (1 + mantissa/2^23) * 2 ^ (exponent-127)
         * We convert the integer equation by factoring a 2^23 out of the
         * exponent
         *  value = (1 + mantissa/2^23) * 2^23 * 2 ^ (exponent-127-23)
         *  value = (2^23 + mantissa) * 2 ^ (exponent-127-23)
         * Because of the implied 1 in front of the mantissa we have 24 bits of
         * precision.
         *   m = (2^23 + mantissa)
         *   e = (exponent-127-23)
         */
        mantissa            = (1UL << 23) | floatMantissa;
        exponent            = floatExponent - 127 - 23;
        mantissaBit         = 23;
        hasUnequalMargins   = (floatExponent != 1) && (floatMantissa == 0);
    }
    else {
        /*
         * denormalized
         * The floating point equation is:
         *  value = (mantissa/2^23) * 2 ^ (1-127)
         * We convert the integer equation by factoring a 2^23 out of the
         * exponent
         *  value = (mantissa/2^23) * 2^23 * 2 ^ (1-127-23)
         *  value = mantissa * 2 ^ (1-127-23)
         * We have up to 23 bits of precision.
         *   m = (mantissa)
         *   e = (1-127-23)
         */
        mantissa           = floatMantissa;
        exponent           = 1 - 127 - 23;
        mantissaBit        = LogBase2_32(mantissa);
        hasUnequalMargins  = NPY_FALSE;
    }

    BigInt_Set_uint32(&bigints[0], mantissa);
    return Format_floatbits(buffer, bufferSize, bigints, exponent,
                           signbit, mantissaBit, hasUnequalMargins, opt);
}