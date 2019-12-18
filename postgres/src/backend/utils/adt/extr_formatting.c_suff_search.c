#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int /*<<< orphan*/  len; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ KeySuffix ;

/* Variables and functions */
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const KeySuffix *
suff_search(const char *str, const KeySuffix *suf, int type)
{
	const KeySuffix *s;

	for (s = suf; s->name != NULL; s++)
	{
		if (s->type != type)
			continue;

		if (strncmp(str, s->name, s->len) == 0)
			return s;
	}
	return NULL;
}