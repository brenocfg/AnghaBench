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
struct buffer {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct buffer) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

void
free_buf(struct buffer *buf)
{
    if (buf->data)
    {
        free(buf->data);
    }
    CLEAR(*buf);
}