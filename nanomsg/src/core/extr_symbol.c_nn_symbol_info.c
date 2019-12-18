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
struct nn_symbol_properties {int dummy; } ;

/* Variables and functions */
 int SYM_VALUE_NAMES_LEN ; 
 int /*<<< orphan*/  memcpy (struct nn_symbol_properties*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sym_value_names ; 

int nn_symbol_info (int i, struct nn_symbol_properties *buf, int buflen)
{
    if (i < 0 || i >= SYM_VALUE_NAMES_LEN) {
        return 0;
    }
    if (buflen > (int)sizeof (struct nn_symbol_properties)) {
        buflen = (int)sizeof (struct nn_symbol_properties);
    }
    memcpy(buf, &sym_value_names [i], buflen);
    return buflen;
}