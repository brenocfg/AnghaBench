#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct MPContext {int open_active; int open_url_flags; int open_for_prefetch; int /*<<< orphan*/  open_thread; TYPE_1__* opts; void* open_format; void* open_url; scalar_t__ open_cancel; int /*<<< orphan*/  open_done; int /*<<< orphan*/  open_res_demuxer; } ;
struct TYPE_2__ {char* demuxer_name; scalar_t__ load_unsafe_playlists; scalar_t__ demuxer_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_open (struct MPContext*) ; 
 scalar_t__ mp_cancel_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_demux_thread ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct MPContext*) ; 
 void* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void start_open(struct MPContext *mpctx, char *url, int url_flags,
                       bool for_prefetch)
{
    cancel_open(mpctx);

    assert(!mpctx->open_active);
    assert(!mpctx->open_cancel);
    assert(!mpctx->open_res_demuxer);
    assert(!atomic_load(&mpctx->open_done));

    mpctx->open_cancel = mp_cancel_new(NULL);
    mpctx->open_url = talloc_strdup(NULL, url);
    mpctx->open_format = talloc_strdup(NULL, mpctx->opts->demuxer_name);
    mpctx->open_url_flags = url_flags;
    mpctx->open_for_prefetch = for_prefetch && mpctx->opts->demuxer_thread;
    if (mpctx->opts->load_unsafe_playlists)
        mpctx->open_url_flags = 0;

    if (pthread_create(&mpctx->open_thread, NULL, open_demux_thread, mpctx)) {
        cancel_open(mpctx);
        return;
    }

    mpctx->open_active = true;
}