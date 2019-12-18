#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ curr; int /*<<< orphan*/  total_blocks; int /*<<< orphan*/  secure_blocks; TYPE_1__* params; } ;
struct TYPE_6__ {char const* key; int type; int size; int secure; scalar_t__ alloc_blocks; } ;
typedef  TYPE_1__ OSSL_PARAM_BLD_DEF ;
typedef  TYPE_2__ OSSL_PARAM_BLD ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_PARAM_PUSH ; 
 int /*<<< orphan*/  CRYPTO_R_TOO_MANY_RECORDS ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OSSL_PARAM_BLD_MAX ; 
 scalar_t__ bytes_to_blocks (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static OSSL_PARAM_BLD_DEF *param_push(OSSL_PARAM_BLD *bld, const char *key,
                                      int size, size_t alloc, int type,
                                      int secure)
{
    OSSL_PARAM_BLD_DEF *pd;

    if (bld->curr >= OSSL_PARAM_BLD_MAX) {
        CRYPTOerr(CRYPTO_F_PARAM_PUSH, CRYPTO_R_TOO_MANY_RECORDS);
        return NULL;
    }
    pd = bld->params + bld->curr++;
    memset(pd, 0, sizeof(*pd));
    pd->key = key;
    pd->type = type;
    pd->size = size;
    pd->alloc_blocks = bytes_to_blocks(size);
    if ((pd->secure = secure) != 0)
        bld->secure_blocks += pd->alloc_blocks;
    else
        bld->total_blocks += pd->alloc_blocks;
    return pd;
}