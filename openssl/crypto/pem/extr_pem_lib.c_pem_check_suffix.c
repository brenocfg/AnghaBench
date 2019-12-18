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
 scalar_t__ strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 

int pem_check_suffix(const char *pem_str, const char *suffix)
{
    int pem_len = strlen(pem_str);
    int suffix_len = strlen(suffix);
    const char *p;
    if (suffix_len + 1 >= pem_len)
        return 0;
    p = pem_str + pem_len - suffix_len;
    if (strcmp(p, suffix))
        return 0;
    p--;
    if (*p != ' ')
        return 0;
    return p - pem_str;
}