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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {char* string; } ;
typedef  TYPE_1__ OSSL_PARAM_BLD_DEF ;
typedef  int /*<<< orphan*/  OSSL_PARAM_BLD ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_OSSL_PARAM_BLD_PUSH_UTF8_PTR ; 
 int /*<<< orphan*/  CRYPTO_R_STRING_TOO_LONG ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  OSSL_PARAM_UTF8_PTR ; 
 TYPE_1__* param_push (int /*<<< orphan*/ *,char const*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

int ossl_param_bld_push_utf8_ptr(OSSL_PARAM_BLD *bld, const char *key,
                                 char *buf, size_t bsize)
{
    OSSL_PARAM_BLD_DEF *pd;

    if (bsize == 0) {
        bsize = strlen(buf) + 1;
    } else if (bsize > INT_MAX) {
        CRYPTOerr(CRYPTO_F_OSSL_PARAM_BLD_PUSH_UTF8_PTR,
                  CRYPTO_R_STRING_TOO_LONG);
        return 0;
    }
    pd = param_push(bld, key, bsize, sizeof(buf), OSSL_PARAM_UTF8_PTR, 0);
    if (pd == NULL)
        return 0;
    pd->string = buf;
    return 1;
}