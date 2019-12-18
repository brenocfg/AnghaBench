#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* output; struct TYPE_6__* osin; int /*<<< orphan*/  input; int /*<<< orphan*/  ctx; } ;
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  TYPE_2__ DIGESTSIGN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int /*<<< orphan*/  evp_test_buffer_free ; 
 int /*<<< orphan*/  sk_EVP_TEST_BUFFER_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void digestsigver_test_cleanup(EVP_TEST *t)
{
    DIGESTSIGN_DATA *mdata = t->data;

    EVP_MD_CTX_free(mdata->ctx);
    sk_EVP_TEST_BUFFER_pop_free(mdata->input, evp_test_buffer_free);
    OPENSSL_free(mdata->osin);
    OPENSSL_free(mdata->output);
    OPENSSL_free(mdata);
    t->data = NULL;
}