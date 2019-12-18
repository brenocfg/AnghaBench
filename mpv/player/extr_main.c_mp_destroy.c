#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct MPContext {int /*<<< orphan*/  abort_lock; struct MPContext* abort_list; int /*<<< orphan*/  num_abort_list; int /*<<< orphan*/  global; int /*<<< orphan*/  input; int /*<<< orphan*/  osd; int /*<<< orphan*/ * encode_lavc_ctx; int /*<<< orphan*/ * ipc_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cas_terminal_owner (struct MPContext*,struct MPContext*) ; 
 int /*<<< orphan*/  cocoa_set_input_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_uninit (struct MPContext*) ; 
 int /*<<< orphan*/  encode_lavc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_clients_destroy (struct MPContext*) ; 
 int /*<<< orphan*/  mp_input_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_msg_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_shutdown_clients (struct MPContext*) ; 
 int /*<<< orphan*/  mp_uninit_ipc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct MPContext*) ; 
 int /*<<< orphan*/  terminal_uninit () ; 
 int /*<<< orphan*/  uninit_audio_out (struct MPContext*) ; 
 int /*<<< orphan*/  uninit_libav (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uninit_video_out (struct MPContext*) ; 

void mp_destroy(struct MPContext *mpctx)
{
    mp_shutdown_clients(mpctx);

    mp_uninit_ipc(mpctx->ipc_ctx);
    mpctx->ipc_ctx = NULL;

    uninit_audio_out(mpctx);
    uninit_video_out(mpctx);

    // If it's still set here, it's an error.
    encode_lavc_free(mpctx->encode_lavc_ctx);
    mpctx->encode_lavc_ctx = NULL;

    command_uninit(mpctx);

    mp_clients_destroy(mpctx);

    osd_free(mpctx->osd);

#if HAVE_COCOA
    cocoa_set_input_context(NULL);
#endif

    if (cas_terminal_owner(mpctx, mpctx)) {
        terminal_uninit();
        cas_terminal_owner(mpctx, NULL);
    }

    mp_input_uninit(mpctx->input);

    uninit_libav(mpctx->global);

    mp_msg_uninit(mpctx->global);
    assert(!mpctx->num_abort_list);
    talloc_free(mpctx->abort_list);
    pthread_mutex_destroy(&mpctx->abort_lock);
    talloc_free(mpctx);
}