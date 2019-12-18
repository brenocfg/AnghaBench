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
typedef  scalar_t__ npy_uint64 ;
typedef  scalar_t__ npy_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ASSERT (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 

__attribute__((used)) static npy_uint32
PrintInfNan(char *buffer, npy_uint32 bufferSize, npy_uint64 mantissa,
            npy_uint32 mantissaHexWidth, char signbit)
{
    npy_uint32 maxPrintLen = bufferSize-1;
    npy_uint32 pos = 0;

    DEBUG_ASSERT(bufferSize > 0);

    /* Check for infinity */
    if (mantissa == 0) {
        npy_uint32 printLen;

        /* only print sign for inf values (though nan can have a sign set) */
        if (signbit == '+') {
            if (pos < maxPrintLen-1) {
                buffer[pos++] = '+';
            }
        }
        else if (signbit == '-') {
            if (pos < maxPrintLen-1) {
                buffer[pos++] = '-';
            }
        }

        /* copy and make sure the buffer is terminated */
        printLen = (3 < maxPrintLen - pos) ? 3 : maxPrintLen - pos;
        memcpy(buffer + pos, "inf", printLen);
        buffer[pos + printLen] = '\0';
        return pos + printLen;
    }
    else {
        /* copy and make sure the buffer is terminated */
        npy_uint32 printLen = (3 < maxPrintLen - pos) ? 3 : maxPrintLen - pos;
        memcpy(buffer + pos, "nan", printLen);
        buffer[pos + printLen] = '\0';

        /*
         *  For numpy we ignore unusual mantissa values for nan, but keep this
         *  code in case we change our mind later.
         *
         * // append HEX value
         * if (maxPrintLen > 3) {
         *     printLen += PrintHex(buffer+3, bufferSize-3, mantissa,
         *                          mantissaHexWidth);
         * }
         */

        return pos + printLen;
    }
}