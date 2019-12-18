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
struct buffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ BLAST (struct buffer*) ; 
 int /*<<< orphan*/  buf_inc_len (struct buffer*,int) ; 
 int /*<<< orphan*/  buf_safe (struct buffer*,int) ; 
 int /*<<< orphan*/  buf_write_u8 (struct buffer*,int /*<<< orphan*/ ) ; 

void
buf_null_terminate(struct buffer *buf)
{
    char *last = (char *) BLAST(buf);
    if (last && *last == '\0') /* already terminated? */
    {
        return;
    }

    if (!buf_safe(buf, 1))   /* make space for trailing null */
    {
        buf_inc_len(buf, -1);
    }

    buf_write_u8(buf, 0);
}