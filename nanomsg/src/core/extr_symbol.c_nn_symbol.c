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
struct nn_symbol_properties {int value; char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SYM_VALUE_NAMES_LEN ; 
 int /*<<< orphan*/  errno ; 
 struct nn_symbol_properties* sym_value_names ; 

const char *nn_symbol (int i, int *value)
{
    const struct nn_symbol_properties *svn;
    if (i < 0 || i >= SYM_VALUE_NAMES_LEN) {
        errno = EINVAL;
        return NULL;
    }

    svn = &sym_value_names [i];
    if (value)
        *value = svn->value;
    return svn->name;
}