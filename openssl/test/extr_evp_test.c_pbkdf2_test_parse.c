#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {scalar_t__ iter; int /*<<< orphan*/ * md; } ;
typedef  TYPE_1__ PBE_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_get_digestbyname (char const*) ; 
 scalar_t__ atoi (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pbkdf2_test_parse(EVP_TEST *t,
                             const char *keyword, const char *value)
{
    PBE_DATA *pdata = t->data;

    if (strcmp(keyword, "iter") == 0) {
        pdata->iter = atoi(value);
        if (pdata->iter <= 0)
            return -1;
        return 1;
    }
    if (strcmp(keyword, "MD") == 0) {
        pdata->md = EVP_get_digestbyname(value);
        if (pdata->md == NULL)
            return -1;
        return 1;
    }
    return 0;
}