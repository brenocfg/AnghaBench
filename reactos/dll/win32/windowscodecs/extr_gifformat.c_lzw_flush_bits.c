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
struct lzw_state {int bits_count; int bits_buf; int (* user_write_data ) (int /*<<< orphan*/ ,unsigned char*,int) ;int /*<<< orphan*/  user_ptr; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int lzw_flush_bits(struct lzw_state *state)
{
    unsigned char byte;

    while (state->bits_count >= 8)
    {
        byte = (unsigned char)state->bits_buf;
        if (state->user_write_data(state->user_ptr, &byte, 1) != 1)
            return 0;
        state->bits_buf >>= 8;
        state->bits_count -= 8;
    }

    if (state->bits_count)
    {
        static const char mask[8] = { 0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f };

        byte = (unsigned char)state->bits_buf & mask[state->bits_count];
        if (state->user_write_data(state->user_ptr, &byte, 1) != 1)
            return 0;
    }

    state->bits_buf = 0;
    state->bits_count = 0;

    return 1;
}