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
struct addr_filter {char* str; int range; int /*<<< orphan*/  filename; int /*<<< orphan*/  sym_to_idx; int /*<<< orphan*/  sym_to; int /*<<< orphan*/  size; int /*<<< orphan*/  sym_from_idx; int /*<<< orphan*/  sym_from; int /*<<< orphan*/  addr; int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  addr_filter__free_str (struct addr_filter*) ; 
 int parse_action (struct addr_filter*) ; 
 int parse_addr_size (char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int parse_num_or_str (char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 

__attribute__((used)) static int parse_one_filter(struct addr_filter *filt, const char **filter_inp)
{
	char *fstr;
	int err;

	filt->str = fstr = strdup(*filter_inp);
	if (!fstr)
		return -ENOMEM;

	err = parse_num_or_str(&fstr, NULL, &filt->action, " ");
	if (err)
		goto out_err;

	err = parse_action(filt);
	if (err)
		goto out_err;

	err = parse_addr_size(&fstr, &filt->addr, &filt->sym_from,
			      &filt->sym_from_idx);
	if (err)
		goto out_err;

	fstr += strspn(fstr, " ");

	if (*fstr == '/') {
		fstr += 1;
		err = parse_addr_size(&fstr, &filt->size, &filt->sym_to,
				      &filt->sym_to_idx);
		if (err)
			goto out_err;
		filt->range = true;
	}

	fstr += strspn(fstr, " ");

	if (*fstr == '@') {
		fstr += 1;
		err = parse_num_or_str(&fstr, NULL, &filt->filename, " ,");
		if (err)
			goto out_err;
	}

	fstr += strspn(fstr, " ,");

	*filter_inp += fstr - filt->str;

	return 0;

out_err:
	addr_filter__free_str(filt);

	return err;
}