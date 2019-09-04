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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_get_digestbyname (char const*) ; 
 int /*<<< orphan*/  opt_printf_stderr (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  prog ; 

int opt_md(const char *name, const EVP_MD **mdp)
{
    *mdp = EVP_get_digestbyname(name);
    if (*mdp != NULL)
        return 1;
    opt_printf_stderr("%s: Unrecognized flag %s\n", prog, name);
    return 0;
}