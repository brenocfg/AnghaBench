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
struct fsg_buffhd {struct fsg_buffhd* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fsg_buffhd*) ; 

__attribute__((used)) static void _fsg_common_free_buffers(struct fsg_buffhd *buffhds, unsigned n)
{
	if (buffhds) {
		struct fsg_buffhd *bh = buffhds;
		while (n--) {
			kfree(bh->buf);
			++bh;
		}
		kfree(buffhds);
	}
}