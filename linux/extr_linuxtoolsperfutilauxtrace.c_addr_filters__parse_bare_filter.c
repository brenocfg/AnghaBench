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
struct addr_filters {int dummy; } ;
struct addr_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_filter__free (struct addr_filter*) ; 
 struct addr_filter* addr_filter__new () ; 
 int /*<<< orphan*/  addr_filters__add (struct addr_filters*,struct addr_filter*) ; 
 int /*<<< orphan*/  addr_filters__exit (struct addr_filters*) ; 
 int parse_one_filter (struct addr_filter*,char const**) ; 

int addr_filters__parse_bare_filter(struct addr_filters *filts,
				    const char *filter)
{
	struct addr_filter *filt;
	const char *fstr = filter;
	int err;

	while (*fstr) {
		filt = addr_filter__new();
		err = parse_one_filter(filt, &fstr);
		if (err) {
			addr_filter__free(filt);
			addr_filters__exit(filts);
			return err;
		}
		addr_filters__add(filts, filt);
	}

	return 0;
}