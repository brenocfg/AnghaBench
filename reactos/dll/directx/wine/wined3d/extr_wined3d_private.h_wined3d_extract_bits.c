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
typedef  unsigned int DWORD ;

/* Variables and functions */
 int CHAR_BIT ; 

__attribute__((used)) static inline DWORD wined3d_extract_bits(const DWORD *bitstream,
        unsigned int offset, unsigned int count)
{
    const unsigned int word_bit_count = sizeof(*bitstream) * CHAR_BIT;
    const unsigned int idx = offset / word_bit_count;
    const unsigned int shift = offset % word_bit_count;
    DWORD mask = (1u << count) - 1;
    DWORD ret;

    ret = (bitstream[idx] >> shift) & mask;
    if (shift + count > word_bit_count)
    {
        const unsigned int extracted_bit_count = word_bit_count - shift;
        const unsigned int remaining_bit_count = count - extracted_bit_count;
        mask = (1u << remaining_bit_count) - 1;
        ret |= (bitstream[idx + 1] & mask) << extracted_bit_count;
    }
    return ret;
}