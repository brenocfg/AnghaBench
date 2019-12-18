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
struct TYPE_4__ {int /*<<< orphan*/  maxmem; int /*<<< orphan*/  r; int /*<<< orphan*/  p; int /*<<< orphan*/  N; } ;
typedef  TYPE_1__ PBE_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 int parse_uint64 (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int scrypt_test_parse(EVP_TEST *t,
                             const char *keyword, const char *value)
{
    PBE_DATA *pdata = t->data;

    if (strcmp(keyword, "N") == 0)
        return parse_uint64(value, &pdata->N);
    if (strcmp(keyword, "p") == 0)
        return parse_uint64(value, &pdata->p);
    if (strcmp(keyword, "r") == 0)
        return parse_uint64(value, &pdata->r);
    if (strcmp(keyword, "maxmem") == 0)
        return parse_uint64(value, &pdata->maxmem);
    return 0;
}