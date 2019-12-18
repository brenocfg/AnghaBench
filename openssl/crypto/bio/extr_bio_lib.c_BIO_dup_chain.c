#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ex_data; int /*<<< orphan*/  num; int /*<<< orphan*/  flags; int /*<<< orphan*/  shutdown; int /*<<< orphan*/  init; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  callback_ex; int /*<<< orphan*/  callback; int /*<<< orphan*/  method; struct TYPE_10__* next_bio; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_dup_state (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  BIO_free (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_free_all (TYPE_1__*) ; 
 TYPE_1__* BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_push (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_BIO ; 
 int /*<<< orphan*/  CRYPTO_dup_ex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BIO *BIO_dup_chain(BIO *in)
{
    BIO *ret = NULL, *eoc = NULL, *bio, *new_bio;

    for (bio = in; bio != NULL; bio = bio->next_bio) {
        if ((new_bio = BIO_new(bio->method)) == NULL)
            goto err;
        new_bio->callback = bio->callback;
        new_bio->callback_ex = bio->callback_ex;
        new_bio->cb_arg = bio->cb_arg;
        new_bio->init = bio->init;
        new_bio->shutdown = bio->shutdown;
        new_bio->flags = bio->flags;

        /* This will let SSL_s_sock() work with stdin/stdout */
        new_bio->num = bio->num;

        if (!BIO_dup_state(bio, (char *)new_bio)) {
            BIO_free(new_bio);
            goto err;
        }

        /* copy app data */
        if (!CRYPTO_dup_ex_data(CRYPTO_EX_INDEX_BIO, &new_bio->ex_data,
                                &bio->ex_data)) {
            BIO_free(new_bio);
            goto err;
        }

        if (ret == NULL) {
            eoc = new_bio;
            ret = eoc;
        } else {
            BIO_push(eoc, new_bio);
            eoc = new_bio;
        }
    }
    return ret;
 err:
    BIO_free_all(ret);

    return NULL;
}