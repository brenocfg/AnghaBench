#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_uint64 ;
typedef  int npy_uint32 ;
struct TYPE_6__ {int length; int* blocks; } ;
typedef  TYPE_1__ BigInt ;

/* Variables and functions */
 scalar_t__ BigInt_Compare (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  DEBUG_ASSERT (int) ; 
 int bitmask_u64 (int) ; 

__attribute__((used)) static npy_uint32
BigInt_DivideWithRemainder_MaxQuotient9(BigInt *dividend, const BigInt *divisor)
{
    npy_uint32 length, quotient;
    const npy_uint32 *finalDivisorBlock;
    npy_uint32 *finalDividendBlock;

    /*
     * Check that the divisor has been correctly shifted into range and that it
     * is not smaller than the dividend in length.
     */
    DEBUG_ASSERT(!divisor->length == 0 &&
                divisor->blocks[divisor->length-1] >= 8 &&
                divisor->blocks[divisor->length-1] < bitmask_u64(32) &&
                dividend->length <= divisor->length);

    /*
     * If the dividend is smaller than the divisor, the quotient is zero and the
     * divisor is already the remainder.
     */
    length = divisor->length;
    if (dividend->length < divisor->length) {
        return 0;
    }

    finalDivisorBlock = divisor->blocks + length - 1;
    finalDividendBlock = dividend->blocks + length - 1;

    /*
     * Compute an estimated quotient based on the high block value. This will
     * either match the actual quotient or undershoot by one.
     */
    quotient = *finalDividendBlock / (*finalDivisorBlock + 1);
    DEBUG_ASSERT(quotient <= 9);

    /* Divide out the estimated quotient */
    if (quotient != 0) {
        /* dividend = dividend - divisor*quotient */
        const npy_uint32 *divisorCur = divisor->blocks;
        npy_uint32 *dividendCur = dividend->blocks;

        npy_uint64 borrow = 0;
        npy_uint64 carry = 0;
        do {
            npy_uint64 difference, product;

            product = (npy_uint64)*divisorCur * (npy_uint64)quotient + carry;
            carry = product >> 32;

            difference = (npy_uint64)*dividendCur
                       - (product & bitmask_u64(32)) - borrow;
            borrow = (difference >> 32) & 1;

            *dividendCur = difference & bitmask_u64(32);

            ++divisorCur;
            ++dividendCur;
        } while(divisorCur <= finalDivisorBlock);

        /* remove all leading zero blocks from dividend */
        while (length > 0 && dividend->blocks[length - 1] == 0) {
            --length;
        }

        dividend->length = length;
    }

    /*
     * If the dividend is still larger than the divisor, we overshot our
     * estimate quotient. To correct, we increment the quotient and subtract one
     * more divisor from the dividend.
     */
    if (BigInt_Compare(dividend, divisor) >= 0) {
        /* dividend = dividend - divisor */
        const npy_uint32 *divisorCur = divisor->blocks;
        npy_uint32 *dividendCur = dividend->blocks;
        npy_uint64 borrow = 0;

        ++quotient;

        do {
            npy_uint64 difference = (npy_uint64)*dividendCur
                                  - (npy_uint64)*divisorCur - borrow;
            borrow = (difference >> 32) & 1;

            *dividendCur = difference & bitmask_u64(32);

            ++divisorCur;
            ++dividendCur;
        } while(divisorCur <= finalDivisorBlock);

        /* remove all leading zero blocks from dividend */
        while (length > 0 && dividend->blocks[length - 1] == 0) {
            --length;
        }

        dividend->length = length;
    }

    return quotient;
}