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
typedef  int /*<<< orphan*/  num ;
typedef  int /*<<< orphan*/  OSSL_PARAM_BLD ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_PARAM_REAL ; 
 int param_push_num (int /*<<< orphan*/ *,char const*,double*,int,int /*<<< orphan*/ ) ; 

int ossl_param_bld_push_double(OSSL_PARAM_BLD *bld, const char *key,
                               double num)
{
    return param_push_num(bld, key, &num, sizeof(num), OSSL_PARAM_REAL);
}