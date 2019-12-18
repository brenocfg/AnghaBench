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
struct rchan_buf {int dummy; } ;
struct pipe_inode_info {int dummy; } ;
struct pipe_buffer {int /*<<< orphan*/  private; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 scalar_t__ page_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relay_consume_bytes (struct rchan_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void relay_pipe_buf_release(struct pipe_inode_info *pipe,
				   struct pipe_buffer *buf)
{
	struct rchan_buf *rbuf;

	rbuf = (struct rchan_buf *)page_private(buf->page);
	relay_consume_bytes(rbuf, buf->private);
}