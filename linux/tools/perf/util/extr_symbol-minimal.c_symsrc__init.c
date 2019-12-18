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
struct symsrc {int fd; int type; int /*<<< orphan*/  name; } ;
struct dso {int /*<<< orphan*/  load_errno; } ;
typedef  enum dso_binary_type { ____Placeholder_dso_binary_type } dso_binary_type ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

int symsrc__init(struct symsrc *ss, struct dso *dso, const char *name,
	         enum dso_binary_type type)
{
	int fd = open(name, O_RDONLY);
	if (fd < 0)
		goto out_errno;

	ss->name = strdup(name);
	if (!ss->name)
		goto out_close;

	ss->fd = fd;
	ss->type = type;

	return 0;
out_close:
	close(fd);
out_errno:
	dso->load_errno = errno;
	return -1;
}