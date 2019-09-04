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

/* Variables and functions */
 char* CRYPTO_malloc (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

char *CRYPTO_strdup(const char *str, const char* file, int line)
{
    char *ret;

    if (str == NULL)
        return NULL;
    ret = CRYPTO_malloc(strlen(str) + 1, file, line);
    if (ret != NULL)
        strcpy(ret, str);
    return ret;
}