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
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_PARAM_OCTET_STRING ; 
 int /*<<< orphan*/  SET_RETURN_SIZE (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int set_string_internal (int /*<<< orphan*/  const*,void const*,size_t,int /*<<< orphan*/ ) ; 

int OSSL_PARAM_set_octet_string(const OSSL_PARAM *p, const void *val,
                                size_t len)
{
    if (p == NULL)
        return 0;

    SET_RETURN_SIZE(p, 0);
    if (val == NULL)
        return 0;
    return set_string_internal(p, val, len, OSSL_PARAM_OCTET_STRING);
}