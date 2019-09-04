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
struct priv {TYPE_2__* current; TYPE_1__* tl; } ;
struct demuxer_params {int skip_lavf_probing; int /*<<< orphan*/  init_fragment; } ;
struct demuxer {int /*<<< orphan*/  global; int /*<<< orphan*/  cancel; struct priv* priv; } ;
struct TYPE_4__ {scalar_t__ d; int /*<<< orphan*/  url; } ;
struct TYPE_3__ {int /*<<< orphan*/  init_fragment; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct demuxer*,char*) ; 
 int /*<<< orphan*/  associate_streams (struct demuxer*,TYPE_2__*) ; 
 int /*<<< orphan*/  close_lazy_segments (struct demuxer*) ; 
 int /*<<< orphan*/  demux_cancel_test (struct demuxer*) ; 
 int /*<<< orphan*/  demux_disable_cache (scalar_t__) ; 
 scalar_t__ demux_open_url (int /*<<< orphan*/ ,struct demuxer_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reopen_lazy_segments(struct demuxer *demuxer)
{
    struct priv *p = demuxer->priv;

    if (p->current->d)
        return;

    close_lazy_segments(demuxer);

    struct demuxer_params params = {
        .init_fragment = p->tl->init_fragment,
        .skip_lavf_probing = true,
    };
    p->current->d = demux_open_url(p->current->url, &params,
                                   demuxer->cancel, demuxer->global);
    if (!p->current->d && !demux_cancel_test(demuxer))
        MP_ERR(demuxer, "failed to load segment\n");
    if (p->current->d)
        demux_disable_cache(p->current->d);
    associate_streams(demuxer, p->current);
}