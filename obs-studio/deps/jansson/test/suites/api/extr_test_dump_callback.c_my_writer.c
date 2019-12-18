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
struct my_sink {size_t cap; size_t off; size_t buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t,char const*,size_t) ; 

__attribute__((used)) static int my_writer(const char *buffer, size_t len, void *data) {
    struct my_sink *s = data;
    if (len > s->cap - s->off) {
        return -1;
    }
    memcpy(s->buf + s->off, buffer, len);
    s->off += len;
    return 0;
}