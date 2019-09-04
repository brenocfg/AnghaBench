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
struct priv {TYPE_1__* tl; int /*<<< orphan*/ * current; } ;
struct demuxer {struct priv* priv; } ;
struct TYPE_2__ {struct demuxer* demuxer; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_lazy_segments (struct demuxer*) ; 
 int /*<<< orphan*/  demux_free (struct demuxer*) ; 
 int /*<<< orphan*/  timeline_destroy (TYPE_1__*) ; 

__attribute__((used)) static void d_close(struct demuxer *demuxer)
{
    struct priv *p = demuxer->priv;
    struct demuxer *master = p->tl->demuxer;
    p->current = NULL;
    close_lazy_segments(demuxer);
    timeline_destroy(p->tl);
    demux_free(master);
}