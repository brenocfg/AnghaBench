#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct TYPE_2__ {struct file* file; } ;
struct aio_kiocb {TYPE_1__ poll; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  aio_complete (struct aio_kiocb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  mangle_poll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void aio_poll_complete(struct aio_kiocb *iocb, __poll_t mask)
{
	struct file *file = iocb->poll.file;

	aio_complete(iocb, mangle_poll(mask), 0);
	fput(file);
}