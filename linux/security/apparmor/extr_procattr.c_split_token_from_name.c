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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  AA_ERROR (char*,char const*,char*) ; 
 int /*<<< orphan*/  EINVAL ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_strtoull (char*,char**,int) ; 

__attribute__((used)) static char *split_token_from_name(const char *op, char *args, u64 *token)
{
	char *name;

	*token = simple_strtoull(args, &name, 16);
	if ((name == args) || *name != '^') {
		AA_ERROR("%s: Invalid input '%s'", op, args);
		return ERR_PTR(-EINVAL);
	}

	name++;			/* skip ^ */
	if (!*name)
		name = NULL;
	return name;
}