#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ return_size; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_PARAM_UTF8_STRING ; 
 int set_string_internal (TYPE_1__*,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

int OSSL_PARAM_set_utf8_string(OSSL_PARAM *p, const char *val)
{
    if (p == NULL)
        return 0;

    p->return_size = 0;
    if (val == NULL)
        return 0;
    return set_string_internal(p, val, strlen(val) + 1, OSSL_PARAM_UTF8_STRING);
}