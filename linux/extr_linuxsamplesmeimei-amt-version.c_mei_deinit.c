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
struct mei {int fd; int initialized; scalar_t__ prot_ver; scalar_t__ buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static void mei_deinit(struct mei *cl)
{
	if (cl->fd != -1)
		close(cl->fd);
	cl->fd = -1;
	cl->buf_size = 0;
	cl->prot_ver = 0;
	cl->initialized = false;
}