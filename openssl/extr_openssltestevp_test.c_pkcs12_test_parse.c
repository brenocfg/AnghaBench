#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {scalar_t__ id; } ;
typedef  TYPE_1__ PBE_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 scalar_t__ atoi (char const*) ; 
 int pbkdf2_test_parse (TYPE_2__*,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pkcs12_test_parse(EVP_TEST *t,
                             const char *keyword, const char *value)
{
    PBE_DATA *pdata = t->data;

    if (strcmp(keyword, "id") == 0) {
        pdata->id = atoi(value);
        if (pdata->id <= 0)
            return -1;
        return 1;
    }
    return pbkdf2_test_parse(t, keyword, value);
}