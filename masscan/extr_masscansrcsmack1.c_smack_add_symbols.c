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
struct SMACK {scalar_t__ is_nocase; } ;

/* Variables and functions */
 int /*<<< orphan*/  smack_add_symbol (struct SMACK*,unsigned char const) ; 
 unsigned char const tolower (unsigned char const) ; 

__attribute__((used)) static void
smack_add_symbols(struct SMACK *smack, const unsigned char *pattern, unsigned pattern_length)
{
    unsigned i;

    /* Add all the bytes in this pattern to the symbol table */
    for (i=0; i<pattern_length; i++) {
        if (smack->is_nocase)
            smack_add_symbol(smack, tolower(pattern[i]));
        else
            smack_add_symbol(smack, pattern[i]);
    }
}