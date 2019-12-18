#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ OSSL_PARAM_BLD_DEF ;
typedef  int /*<<< orphan*/  OSSL_PARAM_BLD ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_PARAM_PUSH_NUM ; 
 int /*<<< orphan*/  CRYPTO_R_TOO_MANY_BYTES ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 
 TYPE_1__* param_push (int /*<<< orphan*/ *,char const*,size_t,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int param_push_num(OSSL_PARAM_BLD *bld, const char *key,
                          void *num, size_t size, int type)
{
    OSSL_PARAM_BLD_DEF *pd = param_push(bld, key, size, size, type, 0);

    if (pd == NULL)
        return 0;
    if (size > sizeof(pd->num)) {
        CRYPTOerr(CRYPTO_F_PARAM_PUSH_NUM, CRYPTO_R_TOO_MANY_BYTES);
        return 0;
    }
    memcpy(&pd->num, num, size);
    return 1;
}