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
struct stream {scalar_t__ seekable; struct priv* priv; } ;
struct priv {size_t cur; int num_streams; int /*<<< orphan*/ * streams; } ;

/* Variables and functions */
 int stream_read_partial (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  stream_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_buffer(struct stream *s, void *buffer, int len)
{
    struct priv *p = s->priv;

    while (1) {
        int res = stream_read_partial(p->streams[p->cur], buffer, len);
        if (res || p->cur == p->num_streams - 1)
            return res;

        p->cur += 1;
        if (s->seekable)
            stream_seek(p->streams[p->cur], 0);
    }
}