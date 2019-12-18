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
 int /*<<< orphan*/  ASN1_STRING_set_default_mask (unsigned long) ; 
 unsigned long B_ASN1_BMPSTRING ; 
 scalar_t__ B_ASN1_T61STRING ; 
 unsigned long B_ASN1_UTF8STRING ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

int ASN1_STRING_set_default_mask_asc(const char *p)
{
    unsigned long mask;
    char *end;

    if (strncmp(p, "MASK:", 5) == 0) {
        if (p[5] == '\0')
            return 0;
        mask = strtoul(p + 5, &end, 0);
        if (*end)
            return 0;
    } else if (strcmp(p, "nombstr") == 0)
        mask = ~((unsigned long)(B_ASN1_BMPSTRING | B_ASN1_UTF8STRING));
    else if (strcmp(p, "pkix") == 0)
        mask = ~((unsigned long)B_ASN1_T61STRING);
    else if (strcmp(p, "utf8only") == 0)
        mask = B_ASN1_UTF8STRING;
    else if (strcmp(p, "default") == 0)
        mask = 0xFFFFFFFFL;
    else
        return 0;
    ASN1_STRING_set_default_mask(mask);
    return 1;
}