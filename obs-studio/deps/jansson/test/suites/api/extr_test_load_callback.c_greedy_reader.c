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
struct my_source {size_t cap; size_t off; size_t buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 

__attribute__((used)) static size_t greedy_reader(void *buf, size_t buflen, void *arg)
{
    struct my_source *s = arg;
    if (buflen > s->cap - s->off)
        buflen = s->cap - s->off;
    if (buflen > 0) {
        memcpy(buf, s->buf + s->off, buflen);
        s->off += buflen;
        return buflen;
    } else {
        return 0;
    }
}