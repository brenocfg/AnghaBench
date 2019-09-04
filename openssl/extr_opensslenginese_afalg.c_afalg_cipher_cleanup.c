#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mode; int /*<<< orphan*/  aio_ctx; int /*<<< orphan*/  efd; } ;
struct TYPE_4__ {scalar_t__ init_done; TYPE_1__ aio; int /*<<< orphan*/  bfd; int /*<<< orphan*/  sfd; } ;
typedef  TYPE_2__ afalg_ctx ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ALG_WARN (char*,char*,...) ; 
 scalar_t__ EVP_CIPHER_CTX_get_cipher_data (int /*<<< orphan*/ *) ; 
 scalar_t__ MAGIC_INIT_NUM ; 
 scalar_t__ MODE_SYNC ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afalg_cipher_cleanup(EVP_CIPHER_CTX *ctx)
{
    afalg_ctx *actx;

    if (ctx == NULL) {
        ALG_WARN("NULL parameter passed to function %s(%d)\n", __FILE__,
                 __LINE__);
        return 0;
    }

    actx = (afalg_ctx *) EVP_CIPHER_CTX_get_cipher_data(ctx);
    if (actx == NULL || actx->init_done != MAGIC_INIT_NUM) {
        ALG_WARN("%s afalg ctx passed\n",
                 ctx == NULL ? "NULL" : "Uninitialised");
        return 0;
    }

    close(actx->sfd);
    close(actx->bfd);
# ifdef ALG_ZERO_COPY
    close(actx->zc_pipe[0]);
    close(actx->zc_pipe[1]);
# endif
    /* close efd in sync mode, async mode is closed in afalg_waitfd_cleanup() */
    if (actx->aio.mode == MODE_SYNC)
        close(actx->aio.efd);
    io_destroy(actx->aio.aio_ctx);

    return 1;
}