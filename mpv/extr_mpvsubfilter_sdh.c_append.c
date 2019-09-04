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
struct sd {int dummy; } ;
struct buffer {scalar_t__ pos; int length; char* string; } ;

/* Variables and functions */

__attribute__((used)) static inline int append(struct sd *sd, struct buffer *buf, char c)
{
    if (buf->pos >= 0 && buf->pos < buf->length) {
        buf->string[buf->pos++] = c;
    } else {
        // ensure that terminating \0 is always written
        if (c == '\0')
            buf->string[buf->length - 1] = c;
    }
    return c;
}