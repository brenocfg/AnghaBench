#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ctl_table; struct ctl_dir* parent; } ;
struct ctl_dir {TYPE_2__ header; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {char* procname; } ;

/* Variables and functions */
 scalar_t__ strscpy (char*,char*,size_t) ; 

__attribute__((used)) static ssize_t sysctl_cpy_dir(const struct ctl_dir *dir, char **bufp,
			      size_t *lenp)
{
	ssize_t tmp_ret = 0, ret;

	if (dir->header.parent) {
		tmp_ret = sysctl_cpy_dir(dir->header.parent, bufp, lenp);
		if (tmp_ret < 0)
			return tmp_ret;
	}

	ret = strscpy(*bufp, dir->header.ctl_table[0].procname, *lenp);
	if (ret < 0)
		return ret;
	*bufp += ret;
	*lenp -= ret;
	ret += tmp_ret;

	/* Avoid leading slash. */
	if (!ret)
		return ret;

	tmp_ret = strscpy(*bufp, "/", *lenp);
	if (tmp_ret < 0)
		return tmp_ret;
	*bufp += tmp_ret;
	*lenp -= tmp_ret;

	return ret + tmp_ret;
}