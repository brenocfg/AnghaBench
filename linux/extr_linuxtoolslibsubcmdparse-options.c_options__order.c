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
struct option {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ OPTION_END ; 
 struct option* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct option*,struct option const*,int) ; 
 int /*<<< orphan*/  option__cmp ; 
 int /*<<< orphan*/  qsort (struct option*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct option *options__order(const struct option *opts)
{
	int nr_opts = 0, len;
	const struct option *o = opts;
	struct option *ordered;

	for (o = opts; o->type != OPTION_END; o++)
		++nr_opts;

	len = sizeof(*o) * (nr_opts + 1);
	ordered = malloc(len);
	if (!ordered)
		goto out;
	memcpy(ordered, opts, len);

	qsort(ordered, nr_opts, sizeof(*o), option__cmp);
out:
	return ordered;
}