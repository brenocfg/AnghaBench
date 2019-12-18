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
typedef  scalar_t__ XXH_endianess ;

/* Variables and functions */
 int /*<<< orphan*/  XXH32_CREATESTATE_STATIC (int /*<<< orphan*/ ) ; 
 unsigned int XXH32_digest (int /*<<< orphan*/ ) ; 
 unsigned int XXH32_endian_align (void const*,size_t,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH32_reset (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XXH32_update (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  XXH_CPU_LITTLE_ENDIAN ; 
 scalar_t__ XXH_FORCE_ALIGN_CHECK ; 
 scalar_t__ XXH_FORCE_NATIVE_FORMAT ; 
 int /*<<< orphan*/  XXH_aligned ; 
 scalar_t__ XXH_bigEndian ; 
 scalar_t__ XXH_littleEndian ; 
 int /*<<< orphan*/  XXH_unaligned ; 
 int /*<<< orphan*/  state ; 

unsigned int XXH32 (const void* input, size_t len, unsigned int seed)
{
#if 0
    /* Simple version, good for code maintenance, but unfortunately slow for small inputs */
    XXH32_CREATESTATE_STATIC(state);
    XXH32_reset(state, seed);
    XXH32_update(state, input, len);
    return XXH32_digest(state);
#else
    XXH_endianess endian_detected = (XXH_endianess)XXH_CPU_LITTLE_ENDIAN;

    if (XXH_FORCE_ALIGN_CHECK) {
        if ((((size_t)input) & 3) == 0) {   /* Input is 4-bytes aligned, leverage the speed benefit */
            if ((endian_detected==XXH_littleEndian) || XXH_FORCE_NATIVE_FORMAT)
                return XXH32_endian_align(input, len, seed, XXH_littleEndian, XXH_aligned);
            else
                return XXH32_endian_align(input, len, seed, XXH_bigEndian, XXH_aligned);
    }   }

    if ((endian_detected==XXH_littleEndian) || XXH_FORCE_NATIVE_FORMAT)
        return XXH32_endian_align(input, len, seed, XXH_littleEndian, XXH_unaligned);
    else
        return XXH32_endian_align(input, len, seed, XXH_bigEndian, XXH_unaligned);
#endif
}