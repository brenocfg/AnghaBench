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
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_get_cipherbyname (char const*) ; 
 int /*<<< orphan*/  opt_printf_stderr (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  prog ; 

int opt_cipher(const char *name, const EVP_CIPHER **cipherp)
{
    *cipherp = EVP_get_cipherbyname(name);
    if (*cipherp != NULL)
        return 1;
    opt_printf_stderr("%s: Unrecognized flag %s\n", prog, name);
    return 0;
}