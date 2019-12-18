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
struct fs_parse_result {int dummy; } ;
struct fs_parameter {int dummy; } ;
struct fs_context {int dummy; } ;
struct cgroup_fs_context {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_ROOT_MEMORY_LOCAL_EVENTS ; 
 int /*<<< orphan*/  CGRP_ROOT_NS_DELEGATE ; 
 int EINVAL ; 
#define  Opt_memory_localevents 129 
#define  Opt_nsdelegate 128 
 int /*<<< orphan*/  cgroup2_fs_parameters ; 
 struct cgroup_fs_context* cgroup_fc2context (struct fs_context*) ; 
 int fs_parse (struct fs_context*,int /*<<< orphan*/ *,struct fs_parameter*,struct fs_parse_result*) ; 

__attribute__((used)) static int cgroup2_parse_param(struct fs_context *fc, struct fs_parameter *param)
{
	struct cgroup_fs_context *ctx = cgroup_fc2context(fc);
	struct fs_parse_result result;
	int opt;

	opt = fs_parse(fc, &cgroup2_fs_parameters, param, &result);
	if (opt < 0)
		return opt;

	switch (opt) {
	case Opt_nsdelegate:
		ctx->flags |= CGRP_ROOT_NS_DELEGATE;
		return 0;
	case Opt_memory_localevents:
		ctx->flags |= CGRP_ROOT_MEMORY_LOCAL_EVENTS;
		return 0;
	}
	return -EINVAL;
}