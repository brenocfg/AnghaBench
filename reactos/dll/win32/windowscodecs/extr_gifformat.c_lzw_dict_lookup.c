#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {short* prefix; unsigned char* suffix; } ;
struct lzw_state {short next_code; TYPE_1__ dict; } ;

/* Variables and functions */

__attribute__((used)) static short lzw_dict_lookup(const struct lzw_state *state, short prefix, unsigned char suffix)
{
    short i;

    for (i = 0; i < state->next_code; i++)
    {
        if (state->dict.prefix[i] == prefix && state->dict.suffix[i] == suffix)
            return i;
    }

    return -1;
}