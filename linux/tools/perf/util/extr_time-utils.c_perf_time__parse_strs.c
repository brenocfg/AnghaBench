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
struct perf_time_interval {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int perf_time__parse_str (struct perf_time_interval*,char*) ; 
 char* skip_spaces (scalar_t__) ; 
 scalar_t__ strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int perf_time__parse_strs(struct perf_time_interval *ptime,
				 const char *ostr, int size)
{
	const char *cp;
	char *str, *arg, *p;
	int i, num = 0, rc = 0;

	/* Count the commas */
	for (cp = ostr; *cp; cp++)
		num += !!(*cp == ',');

	if (!num)
		return -EINVAL;

	BUG_ON(num > size);

	str = strdup(ostr);
	if (!str)
		return -ENOMEM;

	/* Split the string and parse each piece, except the last */
	for (i = 0, p = str; i < num - 1; i++) {
		arg = p;
		/* Find next comma, there must be one */
		p = skip_spaces(strchr(p, ',') + 1);
		/* Skip the value, must not contain space or comma */
		while (*p && !isspace(*p)) {
			if (*p++ == ',') {
				rc = -EINVAL;
				goto out;
			}
		}
		/* Split and parse */
		if (*p)
			*p++ = 0;
		rc = perf_time__parse_str(ptime + i, arg);
		if (rc < 0)
			goto out;
	}

	/* Parse the last piece */
	rc = perf_time__parse_str(ptime + i, p);
	if (rc < 0)
		goto out;

	/* Check there is no overlap */
	for (i = 0; i < num - 1; i++) {
		if (ptime[i].end >= ptime[i + 1].start) {
			rc = -EINVAL;
			goto out;
		}
	}

	rc = num;
out:
	free(str);

	return rc;
}