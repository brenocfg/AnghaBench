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
struct zoran_fh {int dummy; } ;
struct v4l2_buffer {int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int zoran_v4l2_buffer_status (struct zoran_fh*,struct v4l2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zoran_querybuf(struct file *file, void *__fh, struct v4l2_buffer *buf)
{
	struct zoran_fh *fh = __fh;
	int res;

	res = zoran_v4l2_buffer_status(fh, buf, buf->index);

	return res;
}