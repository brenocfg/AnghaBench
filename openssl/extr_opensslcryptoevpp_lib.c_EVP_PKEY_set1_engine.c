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
struct TYPE_3__ {int /*<<< orphan*/ * pmeth_engine; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_get_pkey_meth (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_ENGINE_LIB ; 
 int /*<<< orphan*/  EVP_F_EVP_PKEY_SET1_ENGINE ; 
 int /*<<< orphan*/  EVP_R_UNSUPPORTED_ALGORITHM ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int EVP_PKEY_set1_engine(EVP_PKEY *pkey, ENGINE *e)
{
    if (e != NULL) {
        if (!ENGINE_init(e)) {
            EVPerr(EVP_F_EVP_PKEY_SET1_ENGINE, ERR_R_ENGINE_LIB);
            return 0;
        }
        if (ENGINE_get_pkey_meth(e, pkey->type) == NULL) {
            ENGINE_finish(e);
            EVPerr(EVP_F_EVP_PKEY_SET1_ENGINE, EVP_R_UNSUPPORTED_ALGORITHM);
            return 0;
        }
    }
    ENGINE_finish(pkey->pmeth_engine);
    pkey->pmeth_engine = e;
    return 1;
}