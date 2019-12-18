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
struct MPContext {int /*<<< orphan*/  clients; int /*<<< orphan*/  mconfig; } ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_7__ {TYPE_1__* clients; } ;
typedef  TYPE_2__ mpv_handle ;
struct TYPE_6__ {int have_terminator; } ;

/* Variables and functions */
 int /*<<< orphan*/  core_thread ; 
 int /*<<< orphan*/  m_config_set_profile (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct MPContext* mp_create () ; 
 int /*<<< orphan*/  mp_destroy (struct MPContext*) ; 
 TYPE_2__* mp_new_client (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpv_terminate_destroy (TYPE_2__*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct MPContext*) ; 

mpv_handle *mpv_create(void)
{
    struct MPContext *mpctx = mp_create();
    if (!mpctx)
        return NULL;

    m_config_set_profile(mpctx->mconfig, "libmpv", 0);

    mpv_handle *ctx = mp_new_client(mpctx->clients, "main");
    if (!ctx) {
        mp_destroy(mpctx);
        return NULL;
    }

    pthread_t thread;
    if (pthread_create(&thread, NULL, core_thread, mpctx) != 0) {
        ctx->clients->have_terminator = true; // avoid blocking
        mpv_terminate_destroy(ctx);
        mp_destroy(mpctx);
        return NULL;
    }

    return ctx;
}