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

/* Variables and functions */
 unsigned int get_encode_size (size_t) ; 

__attribute__((used)) static int right_encode(unsigned char *out, int *out_len, size_t bits)
{
    unsigned int len = get_encode_size(bits);
    int i;

    /* The length is constrained to a single byte: 2040/8 = 255 */
    if (len > 0xFF)
        return 0;

    /* MSB's are at the start of the bytes array */
    for (i = len - 1; i >= 0; --i) {
        out[i] = (unsigned char)(bits & 0xFF);
        bits >>= 8;
    }
    /* Tack the length onto the end */
    out[len] = (unsigned char)len;

    /* The Returned length includes the tacked on byte */
    *out_len = len + 1;
    return 1;
}