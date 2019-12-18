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
struct fs_context {int /*<<< orphan*/  s_iflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_RING_MAGIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SB_I_NOEXEC ; 
 int /*<<< orphan*/  init_pseudo (struct fs_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aio_init_fs_context(struct fs_context *fc)
{
	if (!init_pseudo(fc, AIO_RING_MAGIC))
		return -ENOMEM;
	fc->s_iflags |= SB_I_NOEXEC;
	return 0;
}