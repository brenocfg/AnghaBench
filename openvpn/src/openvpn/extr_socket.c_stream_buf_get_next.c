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
struct buffer {int len; } ;
struct stream_buf {struct buffer next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  D_STREAM_DEBUG ; 
 scalar_t__ buf_defined (struct buffer*) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline void
stream_buf_get_next(struct stream_buf *sb, struct buffer *buf)
{
    dmsg(D_STREAM_DEBUG, "STREAM: GET NEXT len=%d",
         buf_defined(&sb->next) ? sb->next.len : -1);
    ASSERT(buf_defined(&sb->next));
    *buf = sb->next;
}