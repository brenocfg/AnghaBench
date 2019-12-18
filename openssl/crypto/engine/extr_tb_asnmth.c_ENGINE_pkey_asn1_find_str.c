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
struct TYPE_7__ {int /*<<< orphan*/  struct_ref; } ;
struct TYPE_6__ {char const* str; int len; int /*<<< orphan*/  const* ameth; TYPE_2__* e; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_ASN1_METHOD ;
typedef  TYPE_1__ ENGINE_FIND_STR ;
typedef  TYPE_2__ ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_PKEY_ASN1_FIND_STR ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_engine_lock_init ; 
 int /*<<< orphan*/  engine_lock_init ; 
 int /*<<< orphan*/  engine_ref_debug (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  engine_table_doall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  global_engine_lock ; 
 int /*<<< orphan*/  look_str_cb ; 
 int /*<<< orphan*/  pkey_asn1_meth_table ; 

const EVP_PKEY_ASN1_METHOD *ENGINE_pkey_asn1_find_str(ENGINE **pe,
                                                      const char *str,
                                                      int len)
{
    ENGINE_FIND_STR fstr;
    fstr.e = NULL;
    fstr.ameth = NULL;
    fstr.str = str;
    fstr.len = len;

    if (!RUN_ONCE(&engine_lock_init, do_engine_lock_init)) {
        ENGINEerr(ENGINE_F_ENGINE_PKEY_ASN1_FIND_STR, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    CRYPTO_THREAD_write_lock(global_engine_lock);
    engine_table_doall(pkey_asn1_meth_table, look_str_cb, &fstr);
    /* If found obtain a structural reference to engine */
    if (fstr.e) {
        fstr.e->struct_ref++;
        engine_ref_debug(fstr.e, 0, 1);
    }
    *pe = fstr.e;
    CRYPTO_THREAD_unlock(global_engine_lock);
    return fstr.ameth;
}