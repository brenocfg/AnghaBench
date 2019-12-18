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
struct sevent {scalar_t__ name; scalar_t__ topic; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cmp_sevent(const void *a, const void *b)
{
	const struct sevent *as = a;
	const struct sevent *bs = b;

	/* Put extra events last */
	if (!!as->desc != !!bs->desc)
		return !!as->desc - !!bs->desc;
	if (as->topic && bs->topic) {
		int n = strcmp(as->topic, bs->topic);

		if (n)
			return n;
	}
	return strcmp(as->name, bs->name);
}