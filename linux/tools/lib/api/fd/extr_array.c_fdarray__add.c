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
struct fdarray {int nr; int nr_alloc; TYPE_1__* entries; int /*<<< orphan*/  nr_autogrow; } ;
struct TYPE_2__ {int fd; short events; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ fdarray__grow (struct fdarray*,int /*<<< orphan*/ ) ; 

int fdarray__add(struct fdarray *fda, int fd, short revents)
{
	int pos = fda->nr;

	if (fda->nr == fda->nr_alloc &&
	    fdarray__grow(fda, fda->nr_autogrow) < 0)
		return -ENOMEM;

	fda->entries[fda->nr].fd     = fd;
	fda->entries[fda->nr].events = revents;
	fda->nr++;
	return pos;
}