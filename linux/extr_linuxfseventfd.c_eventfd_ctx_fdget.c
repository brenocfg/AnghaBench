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
struct fd {int /*<<< orphan*/  file; } ;
struct eventfd_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 struct eventfd_ctx* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct eventfd_ctx* eventfd_ctx_fileget (int /*<<< orphan*/ ) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 

struct eventfd_ctx *eventfd_ctx_fdget(int fd)
{
	struct eventfd_ctx *ctx;
	struct fd f = fdget(fd);
	if (!f.file)
		return ERR_PTR(-EBADF);
	ctx = eventfd_ctx_fileget(f.file);
	fdput(f);
	return ctx;
}