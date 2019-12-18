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
struct stream {unsigned int buf_end; unsigned int buf_cur; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 unsigned int MPMIN (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  stream_read_more (struct stream*,int) ; 

__attribute__((used)) static bool stream_skip_read(struct stream *s, int64_t len)
{
    while (len > 0) {
        unsigned int left = s->buf_end - s->buf_cur;
        if (!left) {
            if (!stream_read_more(s, 1))
                return false;
            continue;
        }
        unsigned skip = MPMIN(len, left);
        s->buf_cur += skip;
        len -= skip;
    }
    return true;
}