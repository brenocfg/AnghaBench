#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ex_data; TYPE_1__* method; int /*<<< orphan*/ * callback_ex; int /*<<< orphan*/ * callback; int /*<<< orphan*/  references; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* destroy ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CB_FREE ; 
 scalar_t__ CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_BIO ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,TYPE_2__*) ; 
 scalar_t__ bio_call_callback (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int BIO_free(BIO *a)
{
    int ret;

    if (a == NULL)
        return 0;

    if (CRYPTO_DOWN_REF(&a->references, &ret, a->lock) <= 0)
        return 0;

    REF_PRINT_COUNT("BIO", a);
    if (ret > 0)
        return 1;
    REF_ASSERT_ISNT(ret < 0);

    if (a->callback != NULL || a->callback_ex != NULL) {
        ret = (int)bio_call_callback(a, BIO_CB_FREE, NULL, 0, 0, 0L, 1L, NULL);
        if (ret <= 0)
            return ret;
    }

    if ((a->method != NULL) && (a->method->destroy != NULL))
        a->method->destroy(a);

    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_BIO, a, &a->ex_data);

    CRYPTO_THREAD_lock_free(a->lock);

    OPENSSL_free(a);

    return 1;
}