#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  objs; } ;
typedef  TYPE_2__ X509_STORE ;
struct TYPE_10__ {int /*<<< orphan*/ * x509; int /*<<< orphan*/ * crl; } ;
struct TYPE_12__ {TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ X509_OBJECT ;
typedef  int /*<<< orphan*/  X509_CRL ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_LU_CRL ; 
 int /*<<< orphan*/  X509_LU_X509 ; 
 int /*<<< orphan*/  X509_OBJECT_free (TYPE_3__*) ; 
 TYPE_3__* X509_OBJECT_new () ; 
 scalar_t__ X509_OBJECT_retrieve_match (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  X509_OBJECT_up_ref_count (TYPE_3__*) ; 
 int sk_X509_OBJECT_push (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int x509_store_add(X509_STORE *ctx, void *x, int crl) {
    X509_OBJECT *obj;
    int ret = 0, added = 0;

    if (x == NULL)
        return 0;
    obj = X509_OBJECT_new();
    if (obj == NULL)
        return 0;

    if (crl) {
        obj->type = X509_LU_CRL;
        obj->data.crl = (X509_CRL *)x;
    } else {
        obj->type = X509_LU_X509;
        obj->data.x509 = (X509 *)x;
    }
    X509_OBJECT_up_ref_count(obj);

    CRYPTO_THREAD_write_lock(ctx->lock);

    if (X509_OBJECT_retrieve_match(ctx->objs, obj)) {
        ret = 1;
    } else {
        added = sk_X509_OBJECT_push(ctx->objs, obj);
        ret = added != 0;
    }

    CRYPTO_THREAD_unlock(ctx->lock);

    if (added == 0)             /* obj not pushed */
        X509_OBJECT_free(obj);

    return ret;
}