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
typedef  int /*<<< orphan*/  sym ;
struct nn_symbol_properties {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_errno () ; 
 char* nn_symbol (int,int*) ; 
 int nn_symbol_info (int,struct nn_symbol_properties*,int) ; 

int main ()
{
    int i;
    struct nn_symbol_properties sym;
    int value;

    nn_assert (nn_symbol (-1, NULL) == NULL);
    nn_assert (nn_errno () == EINVAL);
    nn_assert (nn_symbol_info (-1, &sym, (int) sizeof (sym)) == 0);

    nn_assert (nn_symbol (2000, NULL) == NULL);
    nn_assert (nn_errno () == EINVAL);
    nn_assert (nn_symbol_info (2000, &sym, (int) sizeof (sym)) == 0);

    nn_assert (nn_symbol (6, &value) != NULL);
    nn_assert (value != 0);
    nn_assert (nn_symbol_info (6, &sym, (int) sizeof (sym)) == sizeof (sym));

    for (i = 0; ; ++i) {
        const char* name = nn_symbol (i, &value);
        if (name == NULL) {
            nn_assert (nn_errno () == EINVAL);
            break;
        }
    }

    for (i = 0; ; ++i) {
        if (nn_symbol_info (i, &sym, sizeof (sym)) == 0)
            break;
    }

    return 0;
}