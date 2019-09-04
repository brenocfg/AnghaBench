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
struct segment {int /*<<< orphan*/ * d; scalar_t__ lazy; } ;
struct priv {int num_segments; struct segment* current; struct segment** segments; } ;
struct demuxer {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  demux_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_lazy_segments(struct demuxer *demuxer)
{
    struct priv *p = demuxer->priv;

    // unload previous segment
    for (int n = 0; n < p->num_segments; n++) {
        struct segment *seg = p->segments[n];
        if (seg != p->current && seg->d && seg->lazy) {
            demux_free(seg->d);
            seg->d = NULL;
        }
    }
}