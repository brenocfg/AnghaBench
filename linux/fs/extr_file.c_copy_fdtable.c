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
struct file {int dummy; } ;
struct fdtable {int max_fds; scalar_t__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  copy_fd_bitmaps (struct fdtable*,struct fdtable*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void copy_fdtable(struct fdtable *nfdt, struct fdtable *ofdt)
{
	unsigned int cpy, set;

	BUG_ON(nfdt->max_fds < ofdt->max_fds);

	cpy = ofdt->max_fds * sizeof(struct file *);
	set = (nfdt->max_fds - ofdt->max_fds) * sizeof(struct file *);
	memcpy(nfdt->fd, ofdt->fd, cpy);
	memset((char *)nfdt->fd + cpy, 0, set);

	copy_fd_bitmaps(nfdt, ofdt, ofdt->max_fds);
}