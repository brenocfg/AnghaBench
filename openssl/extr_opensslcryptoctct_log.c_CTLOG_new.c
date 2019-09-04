#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * public_key; int /*<<< orphan*/  log_id; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_1__ CTLOG ;

/* Variables and functions */
 int /*<<< orphan*/  CTLOG_free (TYPE_1__*) ; 
 int /*<<< orphan*/  CT_F_CTLOG_NEW ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int ct_v1_log_id_from_pkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

CTLOG *CTLOG_new(EVP_PKEY *public_key, const char *name)
{
    CTLOG *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL) {
        CTerr(CT_F_CTLOG_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    ret->name = OPENSSL_strdup(name);
    if (ret->name == NULL) {
        CTerr(CT_F_CTLOG_NEW, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (ct_v1_log_id_from_pkey(public_key, ret->log_id) != 1)
        goto err;

    ret->public_key = public_key;
    return ret;
err:
    CTLOG_free(ret);
    return NULL;
}