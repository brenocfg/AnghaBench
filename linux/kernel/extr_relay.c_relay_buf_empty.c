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
struct rchan_buf {scalar_t__ subbufs_consumed; scalar_t__ subbufs_produced; } ;

/* Variables and functions */

__attribute__((used)) static int relay_buf_empty(struct rchan_buf *buf)
{
	return (buf->subbufs_produced - buf->subbufs_consumed) ? 0 : 1;
}