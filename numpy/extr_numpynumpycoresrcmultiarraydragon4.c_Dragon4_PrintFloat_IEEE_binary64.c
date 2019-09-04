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
typedef  unsigned long long npy_uint64 ;
typedef  int npy_uint32 ;
typedef  int npy_int32 ;
typedef  int /*<<< orphan*/  npy_float64 ;
typedef  int npy_bool ;
struct TYPE_7__ {scalar_t__ sign; } ;
struct TYPE_6__ {char* repr; int /*<<< orphan*/ * bigints; } ;
typedef  TYPE_1__ Dragon4_Scratch ;
typedef  TYPE_2__ Dragon4_Options ;
typedef  int /*<<< orphan*/  BigInt ;

/* Variables and functions */
 int /*<<< orphan*/  BigInt_Set_uint64 (int /*<<< orphan*/ *,unsigned long long) ; 
 int Format_floatbits (char*,int,int /*<<< orphan*/ *,int,char,int,int,TYPE_2__*) ; 
 int LogBase2_64 (unsigned long long) ; 
 int NPY_FALSE ; 
 int PrintInfNan (char*,int,unsigned long long,int,char) ; 
 int bitmask_u32 (int) ; 
 unsigned long long bitmask_u64 (int) ; 

__attribute__((used)) static npy_uint32
Dragon4_PrintFloat_IEEE_binary64(
        Dragon4_Scratch *scratch, npy_float64 *value, Dragon4_Options *opt)
{
    char *buffer = scratch->repr;
    npy_uint32 bufferSize = sizeof(scratch->repr);
    BigInt *bigints = scratch->bigints;

    union
    {
        npy_float64 floatingPoint;
        npy_uint64 integer;
    } floatUnion;
    npy_uint32 floatExponent, floatSign;
    npy_uint64 floatMantissa;

    npy_uint64 mantissa;
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
    floatMantissa = floatUnion.integer & bitmask_u64(52);
    floatExponent = (floatUnion.integer >> 52) & bitmask_u32(11);
    floatSign = floatUnion.integer >> 63;

    /* output the sign */
    if (floatSign != 0) {
        signbit = '-';
    }
    else if (opt->sign) {
        signbit = '+';
    }

    /* if this is a special value */
    if (floatExponent == bitmask_u32(11)) {
        return PrintInfNan(buffer, bufferSize, floatMantissa, 13, signbit);
    }
    /* else this is a number */

    /* factor the value into its parts */
    if (floatExponent != 0) {
        /*
         * normal
         * The floating point equation is:
         *  value = (1 + mantissa/2^52) * 2 ^ (exponent-1023)
         * We convert the integer equation by factoring a 2^52 out of the
         * exponent
         *  value = (1 + mantissa/2^52) * 2^52 * 2 ^ (exponent-1023-52)
         *  value = (2^52 + mantissa) * 2 ^ (exponent-1023-52)
         * Because of the implied 1 in front of the mantissa we have 53 bits of
         * precision.
         *   m = (2^52 + mantissa)
         *   e = (exponent-1023+1-53)
         */
        mantissa            = (1ull << 52) | floatMantissa;
        exponent            = floatExponent - 1023 - 52;
        mantissaBit         = 52;
        hasUnequalMargins   = (floatExponent != 1) && (floatMantissa == 0);
    }
    else {
        /*
         * subnormal
         * The floating point equation is:
         *  value = (mantissa/2^52) * 2 ^ (1-1023)
         * We convert the integer equation by factoring a 2^52 out of the
         * exponent
         *  value = (mantissa/2^52) * 2^52 * 2 ^ (1-1023-52)
         *  value = mantissa * 2 ^ (1-1023-52)
         * We have up to 52 bits of precision.
         *   m = (mantissa)
         *   e = (1-1023-52)
         */
        mantissa            = floatMantissa;
        exponent            = 1 - 1023 - 52;
        mantissaBit         = LogBase2_64(mantissa);
        hasUnequalMargins   = NPY_FALSE;
    }

    BigInt_Set_uint64(&bigints[0], mantissa);
    return Format_floatbits(buffer, bufferSize, bigints, exponent,
                            signbit, mantissaBit, hasUnequalMargins, opt);
}