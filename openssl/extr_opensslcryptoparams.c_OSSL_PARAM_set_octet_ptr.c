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
 int /*<<< orphan*/  OSSL_PARAM_OCTET_PTR ; 
 int /*<<< orphan*/  SET_RETURN_SIZE (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int set_ptr_internal (int /*<<< orphan*/  const*,void const*,int /*<<< orphan*/ ,size_t) ; 

int OSSL_PARAM_set_octet_ptr(const OSSL_PARAM *p, const void *val,
                             size_t used_len)
{
    if (p == NULL)
        return 0;
    SET_RETURN_SIZE(p, 0);
    if (val == NULL)
        return 0;
    return set_ptr_internal(p, val, OSSL_PARAM_OCTET_PTR, used_len);
}