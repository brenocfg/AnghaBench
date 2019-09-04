#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int struct_ref; int /*<<< orphan*/  ex_data; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_ENGINE ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_NEW ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_engine_lock_init ; 
 int /*<<< orphan*/  engine_lock_init ; 
 int /*<<< orphan*/  engine_ref_debug (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

ENGINE *ENGINE_new(void)
{
    ENGINE *ret;

    if (!RUN_ONCE(&engine_lock_init, do_engine_lock_init)
        || (ret = OPENSSL_zalloc(sizeof(*ret))) == NULL) {
        ENGINEerr(ENGINE_F_ENGINE_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->struct_ref = 1;
    engine_ref_debug(ret, 0, 1);
    if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_ENGINE, ret, &ret->ex_data)) {
        OPENSSL_free(ret);
        return NULL;
    }
    return ret;
}