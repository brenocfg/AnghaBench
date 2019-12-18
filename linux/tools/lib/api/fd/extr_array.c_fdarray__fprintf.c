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
struct fdarray {int nr; TYPE_1__* entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fprintf (int /*<<< orphan*/ *,char*,...) ; 

int fdarray__fprintf(struct fdarray *fda, FILE *fp)
{
	int fd, printed = fprintf(fp, "%d [ ", fda->nr);

	for (fd = 0; fd < fda->nr; ++fd)
		printed += fprintf(fp, "%s%d", fd ? ", " : "", fda->entries[fd].fd);

	return printed + fprintf(fp, " ]");
}