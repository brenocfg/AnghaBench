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
struct mp_waiter {int dummy; } ;
struct MPContext {int /*<<< orphan*/  playback_abort; TYPE_1__* opts; } ;
struct TYPE_2__ {int /*<<< orphan*/  external_files; int /*<<< orphan*/  sub_name; int /*<<< orphan*/  audio_files; } ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_AUDIO ; 
 int /*<<< orphan*/  STREAM_SUB ; 
 int /*<<< orphan*/  STREAM_TYPE_COUNT ; 
 int /*<<< orphan*/  autoload_external_files (struct MPContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_chapters (struct MPContext*) ; 
 int /*<<< orphan*/  mp_core_lock (struct MPContext*) ; 
 int /*<<< orphan*/  mp_core_unlock (struct MPContext*) ; 
 int /*<<< orphan*/  mp_waiter_wakeup (struct mp_waiter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  open_external_files (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_external_opts_thread(void *p)
{
    void **a = p;
    struct MPContext *mpctx = a[0];
    struct mp_waiter *waiter = a[1];

    mp_core_lock(mpctx);

    load_chapters(mpctx);
    open_external_files(mpctx, mpctx->opts->audio_files, STREAM_AUDIO);
    open_external_files(mpctx, mpctx->opts->sub_name, STREAM_SUB);
    open_external_files(mpctx, mpctx->opts->external_files, STREAM_TYPE_COUNT);
    autoload_external_files(mpctx, mpctx->playback_abort);

    mp_waiter_wakeup(waiter, 0);
    mp_wakeup_core(mpctx);
    mp_core_unlock(mpctx);
}