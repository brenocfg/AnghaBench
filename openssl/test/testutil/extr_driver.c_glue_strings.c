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
 char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 char const* strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

char *glue_strings(const char *list[], size_t *out_len)
{
    size_t len = 0;
    char *p, *ret;
    int i;

    for (i = 0; list[i] != NULL; i++)
        len += strlen(list[i]);

    if (out_len != NULL)
        *out_len = len;

    if (!TEST_ptr(ret = p = OPENSSL_malloc(len + 1)))
        return NULL;

    for (i = 0; list[i] != NULL; i++)
        p += strlen(strcpy(p, list[i]));

    return ret;
}