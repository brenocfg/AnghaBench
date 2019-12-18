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
struct record_opts {int use_clockid; int /*<<< orphan*/  clockid_res_ns; int /*<<< orphan*/  clockid; } ;
struct option {scalar_t__ value; } ;
struct clockid_map {int /*<<< orphan*/  clockid; scalar_t__ name; } ;

/* Variables and functions */
 struct clockid_map* clockids ; 
 int get_clockid_res (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 
 int /*<<< orphan*/  ui__warning (char*,char const*) ; 

__attribute__((used)) static int parse_clockid(const struct option *opt, const char *str, int unset)
{
	struct record_opts *opts = (struct record_opts *)opt->value;
	const struct clockid_map *cm;
	const char *ostr = str;

	if (unset) {
		opts->use_clockid = 0;
		return 0;
	}

	/* no arg passed */
	if (!str)
		return 0;

	/* no setting it twice */
	if (opts->use_clockid)
		return -1;

	opts->use_clockid = true;

	/* if its a number, we're done */
	if (sscanf(str, "%d", &opts->clockid) == 1)
		return get_clockid_res(opts->clockid, &opts->clockid_res_ns);

	/* allow a "CLOCK_" prefix to the name */
	if (!strncasecmp(str, "CLOCK_", 6))
		str += 6;

	for (cm = clockids; cm->name; cm++) {
		if (!strcasecmp(str, cm->name)) {
			opts->clockid = cm->clockid;
			return get_clockid_res(opts->clockid,
					       &opts->clockid_res_ns);
		}
	}

	opts->use_clockid = false;
	ui__warning("unknown clockid %s, check man page\n", ostr);
	return -1;
}