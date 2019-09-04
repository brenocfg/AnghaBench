#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int struct_ref; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  (* destroy ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_ENGINE ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  engine_pkey_asn1_meths_free (TYPE_1__*) ; 
 int /*<<< orphan*/  engine_pkey_meths_free (TYPE_1__*) ; 
 int /*<<< orphan*/  engine_ref_debug (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  global_engine_lock ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

int engine_free_util(ENGINE *e, int not_locked)
{
    int i;

    if (e == NULL)
        return 1;
    if (not_locked)
        CRYPTO_DOWN_REF(&e->struct_ref, &i, global_engine_lock);
    else
        i = --e->struct_ref;
    engine_ref_debug(e, 0, -1);
    if (i > 0)
        return 1;
    REF_ASSERT_ISNT(i < 0);
    /* Free up any dynamically allocated public key methods */
    engine_pkey_meths_free(e);
    engine_pkey_asn1_meths_free(e);
    /*
     * Give the ENGINE a chance to do any structural cleanup corresponding to
     * allocation it did in its constructor (eg. unload error strings)
     */
    if (e->destroy)
        e->destroy(e);
    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_ENGINE, e, &e->ex_data);
    OPENSSL_free(e);
    return 1;
}