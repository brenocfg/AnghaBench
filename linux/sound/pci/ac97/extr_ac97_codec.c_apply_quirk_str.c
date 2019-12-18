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
struct snd_ac97 {int dummy; } ;
struct quirk_table {scalar_t__ name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct quirk_table*) ; 
 int EINVAL ; 
 struct quirk_table* applicable_quirks ; 
 int apply_quirk (struct snd_ac97*,int) ; 
 scalar_t__ simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int apply_quirk_str(struct snd_ac97 *ac97, const char *typestr)
{
	int i;
	struct quirk_table *q;

	for (i = 0; i < ARRAY_SIZE(applicable_quirks); i++) {
		q = &applicable_quirks[i];
		if (q->name && ! strcmp(typestr, q->name))
			return apply_quirk(ac97, i);
	}
	/* for compatibility, accept the numbers, too */
	if (*typestr >= '0' && *typestr <= '9')
		return apply_quirk(ac97, (int)simple_strtoul(typestr, NULL, 10));
	return -EINVAL;
}