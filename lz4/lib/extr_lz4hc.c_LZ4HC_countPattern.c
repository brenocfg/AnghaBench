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
typedef  int reg_t ;
typedef  int /*<<< orphan*/  pattern ;
typedef  int U32 ;
typedef  scalar_t__ const BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4_NbCommonBytes (int const) ; 
 scalar_t__ LZ4_isLittleEndian () ; 
 int const LZ4_read_ARCH (scalar_t__ const*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static unsigned
LZ4HC_countPattern(const BYTE* ip, const BYTE* const iEnd, U32 const pattern32)
{
    const BYTE* const iStart = ip;
    reg_t const pattern = (sizeof(pattern)==8) ? (reg_t)pattern32 + (((reg_t)pattern32) << 32) : pattern32;

    while (likely(ip < iEnd-(sizeof(pattern)-1))) {
        reg_t const diff = LZ4_read_ARCH(ip) ^ pattern;
        if (!diff) { ip+=sizeof(pattern); continue; }
        ip += LZ4_NbCommonBytes(diff);
        return (unsigned)(ip - iStart);
    }

    if (LZ4_isLittleEndian()) {
        reg_t patternByte = pattern;
        while ((ip<iEnd) && (*ip == (BYTE)patternByte)) {
            ip++; patternByte >>= 8;
        }
    } else {  /* big endian */
        U32 bitOffset = (sizeof(pattern)*8) - 8;
        while (ip < iEnd) {
            BYTE const byte = (BYTE)(pattern >> bitOffset);
            if (*ip != byte) break;
            ip ++; bitOffset -= 8;
        }
    }

    return (unsigned)(ip - iStart);
}