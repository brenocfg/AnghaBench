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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_PARAM_INTEGER ; 
 int /*<<< orphan*/  ossl_param_construct (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

OSSL_PARAM OSSL_PARAM_construct_int32(const char *key, int32_t *buf)
{
    return ossl_param_construct(key, OSSL_PARAM_INTEGER, buf,
                                sizeof(int32_t));
}