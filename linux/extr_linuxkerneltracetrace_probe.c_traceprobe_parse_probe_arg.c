#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  fn; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  fn; } ;
struct probe_arg {char const* comm; TYPE_3__ fetch; TYPE_1__ fetch_size; TYPE_2__* type; int /*<<< orphan*/  offset; } ;
struct fetch_type {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_9__ {scalar_t__ size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_ARGSTR_LEN ; 
 int __parse_bitfield_probe_arg (char const*,TYPE_2__*,TYPE_3__*) ; 
 TYPE_2__* find_fetch_type (char const*,struct fetch_type const*) ; 
 int /*<<< orphan*/  get_fetch_size_function (TYPE_2__*,int /*<<< orphan*/ ,struct fetch_type const*) ; 
 char const* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int parse_probe_arg (char*,TYPE_2__*,TYPE_3__*,int,int,struct fetch_type const*) ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int traceprobe_parse_probe_arg(char *arg, ssize_t *size,
		struct probe_arg *parg, bool is_return, bool is_kprobe,
		const struct fetch_type *ftbl)
{
	const char *t;
	int ret;

	if (strlen(arg) > MAX_ARGSTR_LEN) {
		pr_info("Argument is too long.: %s\n",  arg);
		return -ENOSPC;
	}
	parg->comm = kstrdup(arg, GFP_KERNEL);
	if (!parg->comm) {
		pr_info("Failed to allocate memory for command '%s'.\n", arg);
		return -ENOMEM;
	}
	t = strchr(parg->comm, ':');
	if (t) {
		arg[t - parg->comm] = '\0';
		t++;
	}
	/*
	 * The default type of $comm should be "string", and it can't be
	 * dereferenced.
	 */
	if (!t && strcmp(arg, "$comm") == 0)
		t = "string";
	parg->type = find_fetch_type(t, ftbl);
	if (!parg->type) {
		pr_info("Unsupported type: %s\n", t);
		return -EINVAL;
	}
	parg->offset = *size;
	*size += parg->type->size;
	ret = parse_probe_arg(arg, parg->type, &parg->fetch, is_return,
			      is_kprobe, ftbl);

	if (ret >= 0 && t != NULL)
		ret = __parse_bitfield_probe_arg(t, parg->type, &parg->fetch);

	if (ret >= 0) {
		parg->fetch_size.fn = get_fetch_size_function(parg->type,
							      parg->fetch.fn,
							      ftbl);
		parg->fetch_size.data = parg->fetch.data;
	}

	return ret;
}