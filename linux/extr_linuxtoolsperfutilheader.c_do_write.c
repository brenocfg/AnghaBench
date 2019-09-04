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
struct feat_fd {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int __do_write_buf (struct feat_fd*,void const*,size_t) ; 
 int __do_write_fd (struct feat_fd*,void const*,size_t) ; 

int do_write(struct feat_fd *ff, const void *buf, size_t size)
{
	if (!ff->buf)
		return __do_write_fd(ff, buf, size);
	return __do_write_buf(ff, buf, size);
}