#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* ctx; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
struct TYPE_12__ {int /*<<< orphan*/  get_cert_methods; int /*<<< orphan*/  lock; int /*<<< orphan*/  objs; } ;
typedef  TYPE_3__ X509_STORE ;
struct TYPE_10__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_13__ {TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ X509_OBJECT ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509_LOOKUP_TYPE ;
typedef  int /*<<< orphan*/  X509_LOOKUP ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int X509_LOOKUP_by_subject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  X509_LU_CRL ; 
 int /*<<< orphan*/  X509_LU_NONE ; 
 TYPE_4__* X509_OBJECT_retrieve_by_subject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_OBJECT_up_ref_count (TYPE_4__*) ; 
 int sk_X509_LOOKUP_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_X509_LOOKUP_value (int /*<<< orphan*/ ,int) ; 

int X509_STORE_CTX_get_by_subject(X509_STORE_CTX *vs, X509_LOOKUP_TYPE type,
                                  X509_NAME *name, X509_OBJECT *ret)
{
    X509_STORE *ctx = vs->ctx;
    X509_LOOKUP *lu;
    X509_OBJECT stmp, *tmp;
    int i, j;

    if (ctx == NULL)
        return 0;

    stmp.type = X509_LU_NONE;
    stmp.data.ptr = NULL;

    CRYPTO_THREAD_write_lock(ctx->lock);
    tmp = X509_OBJECT_retrieve_by_subject(ctx->objs, type, name);
    CRYPTO_THREAD_unlock(ctx->lock);

    if (tmp == NULL || type == X509_LU_CRL) {
        for (i = 0; i < sk_X509_LOOKUP_num(ctx->get_cert_methods); i++) {
            lu = sk_X509_LOOKUP_value(ctx->get_cert_methods, i);
            j = X509_LOOKUP_by_subject(lu, type, name, &stmp);
            if (j) {
                tmp = &stmp;
                break;
            }
        }
        if (tmp == NULL)
            return 0;
    }

    ret->type = tmp->type;
    ret->data.ptr = tmp->data.ptr;

    X509_OBJECT_up_ref_count(ret);

    return 1;
}