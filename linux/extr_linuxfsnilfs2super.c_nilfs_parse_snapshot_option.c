#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  from; } ;
typedef  TYPE_1__ substring_t ;
struct nilfs_super_data {int flags; unsigned long long cno; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int SB_RDONLY ; 
 int kstrtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 

__attribute__((used)) static int nilfs_parse_snapshot_option(const char *option,
				       const substring_t *arg,
				       struct nilfs_super_data *sd)
{
	unsigned long long val;
	const char *msg = NULL;
	int err;

	if (!(sd->flags & SB_RDONLY)) {
		msg = "read-only option is not specified";
		goto parse_error;
	}

	err = kstrtoull(arg->from, 0, &val);
	if (err) {
		if (err == -ERANGE)
			msg = "too large checkpoint number";
		else
			msg = "malformed argument";
		goto parse_error;
	} else if (val == 0) {
		msg = "invalid checkpoint number 0";
		goto parse_error;
	}
	sd->cno = val;
	return 0;

parse_error:
	nilfs_msg(NULL, KERN_ERR, "invalid option \"%s\": %s", option, msg);
	return 1;
}