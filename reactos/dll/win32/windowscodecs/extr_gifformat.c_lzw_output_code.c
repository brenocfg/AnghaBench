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
struct lzw_state {short bits_buf; short bits_count; int (* user_write_data ) (int /*<<< orphan*/ ,unsigned char*,int) ;int /*<<< orphan*/  user_ptr; scalar_t__ code_bits; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int lzw_output_code(struct lzw_state *state, short code)
{
    state->bits_buf |= code << state->bits_count;
    state->bits_count += state->code_bits;

    while (state->bits_count >= 8)
    {
        unsigned char byte = (unsigned char)state->bits_buf;
        if (state->user_write_data(state->user_ptr, &byte, 1) != 1)
            return 0;
        state->bits_buf >>= 8;
        state->bits_count -= 8;
    }

    return 1;
}