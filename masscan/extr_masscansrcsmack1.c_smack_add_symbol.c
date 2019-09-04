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
struct SMACK {unsigned int symbol_count; unsigned int* symbol_to_char; unsigned char* char_to_symbol; } ;

/* Variables and functions */

__attribute__((used)) static unsigned
smack_add_symbol(struct SMACK *smack, unsigned c)
{
    unsigned i;
    unsigned symbol;

    /* See if we already know the symbol */
    for (i=1; i<=smack->symbol_count; i++) {
        if (smack->symbol_to_char[i] == c)
            return i;
    }

    /* Add the symbol to our list */
    smack->symbol_count++;
    symbol = smack->symbol_count;

    /* Map it in both directions */
    smack->symbol_to_char[symbol] = c;
    smack->char_to_symbol[c] = (unsigned char)symbol;

    return symbol;
}