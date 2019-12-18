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
struct TYPE_6__ {int loading; scalar_t__ expected_type; TYPE_1__* loader; int /*<<< orphan*/  post_process_data; int /*<<< orphan*/ * (* post_process ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ui_data; int /*<<< orphan*/  ui_method; int /*<<< orphan*/  loader_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/ * expect; int /*<<< orphan*/ * (* load ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;
typedef  TYPE_2__ OSSL_STORE_CTX ;

/* Variables and functions */
 int OSSL_STORE_INFO_NAME ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_free (int /*<<< orphan*/ *) ; 
 int OSSL_STORE_INFO_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_type_string (int) ; 
 scalar_t__ OSSL_STORE_eof (TYPE_2__*) ; 
 int /*<<< orphan*/  OSSL_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSSL_TRACE1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STORE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

OSSL_STORE_INFO *OSSL_STORE_load(OSSL_STORE_CTX *ctx)
{
    OSSL_STORE_INFO *v = NULL;

    ctx->loading = 1;
 again:
    if (OSSL_STORE_eof(ctx))
        return NULL;

    OSSL_TRACE(STORE, "Loading next object\n");
    v = ctx->loader->load(ctx->loader_ctx, ctx->ui_method, ctx->ui_data);

    if (ctx->post_process != NULL && v != NULL) {
        v = ctx->post_process(v, ctx->post_process_data);

        /*
         * By returning NULL, the callback decides that this object should
         * be ignored.
         */
        if (v == NULL)
            goto again;
    }

    if (v != NULL && ctx->expected_type != 0) {
        int returned_type = OSSL_STORE_INFO_get_type(v);

        if (returned_type != OSSL_STORE_INFO_NAME && returned_type != 0) {
            /*
             * Soft assert here so those who want to harsly weed out faulty
             * loaders can do so using a debugging version of libcrypto.
             */
            if (ctx->loader->expect != NULL)
                assert(ctx->expected_type == returned_type);

            if (ctx->expected_type != returned_type) {
                OSSL_STORE_INFO_free(v);
                goto again;
            }
        }
    }

    if (v != NULL)
        OSSL_TRACE1(STORE, "Got a %s\n",
                    OSSL_STORE_INFO_type_string(OSSL_STORE_INFO_get_type(v)));

    return v;
}