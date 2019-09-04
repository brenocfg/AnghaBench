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
struct aa_ext {void* pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kmemdup (char const*,int,int /*<<< orphan*/ ) ; 
 int unpack_str (struct aa_ext*,char const**,char const*) ; 

__attribute__((used)) static int unpack_strdup(struct aa_ext *e, char **string, const char *name)
{
	const char *tmp;
	void *pos = e->pos;
	int res = unpack_str(e, &tmp, name);
	*string = NULL;

	if (!res)
		return 0;

	*string = kmemdup(tmp, res, GFP_KERNEL);
	if (!*string) {
		e->pos = pos;
		return 0;
	}

	return res;
}