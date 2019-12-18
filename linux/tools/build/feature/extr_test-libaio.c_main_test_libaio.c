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
struct TYPE_2__ {int sigev_notify; } ;
struct aiocb {TYPE_1__ aio_sigevent; scalar_t__ aio_reqprio; scalar_t__ aio_nbytes; scalar_t__ aio_buf; scalar_t__ aio_offset; scalar_t__ aio_fildes; } ;

/* Variables and functions */
 scalar_t__ aio_return (struct aiocb*) ; 

int main(void)
{
	struct aiocb aiocb;

	aiocb.aio_fildes  = 0;
	aiocb.aio_offset  = 0;
	aiocb.aio_buf     = 0;
	aiocb.aio_nbytes  = 0;
	aiocb.aio_reqprio = 0;
	aiocb.aio_sigevent.sigev_notify = 1 /*SIGEV_NONE*/;

	return (int)aio_return(&aiocb);
}