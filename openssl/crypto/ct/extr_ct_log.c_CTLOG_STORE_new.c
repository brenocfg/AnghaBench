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
struct TYPE_5__ {int /*<<< orphan*/ * logs; } ;
typedef  TYPE_1__ CTLOG_STORE ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_CTLOG_STORE_NEW ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/ * sk_CTLOG_new_null () ; 

CTLOG_STORE *CTLOG_STORE_new(void)
{
    CTLOG_STORE *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL) {
        CTerr(CT_F_CTLOG_STORE_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    ret->logs = sk_CTLOG_new_null();
    if (ret->logs == NULL)
        goto err;

    return ret;
err:
    OPENSSL_free(ret);
    return NULL;
}