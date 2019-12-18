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
struct stream {scalar_t__ pos; struct priv* priv; } ;
struct priv {int num_streams; int cur; int /*<<< orphan*/ * streams; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ stream_get_size (int /*<<< orphan*/ ) ; 
 int stream_seek (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stream_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seek(struct stream *s, int64_t newpos)
{
    struct priv *p = s->priv;

    int64_t next_pos = 0;
    int64_t base_pos = 0;

    // Look for the last stream whose start position is <= newpos.
    // Note that the last stream's size is essentially ignored. The last
    // stream is allowed to have an unknown size.
    for (int n = 0; n < p->num_streams; n++) {
        if (next_pos > newpos)
            break;

        base_pos = next_pos;
        p->cur = n;

        int64_t size = stream_get_size(p->streams[n]);
        if (size < 0)
            break;

        next_pos = base_pos + size;
    }

    int ok = stream_seek(p->streams[p->cur], newpos - base_pos);
    s->pos = base_pos + stream_tell(p->streams[p->cur]);
    return ok;
}