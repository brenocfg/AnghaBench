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

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *
ecpg_strndup(const char *str, size_t len)
{
	size_t		real_len = strlen(str);
	int			use_len = (int) ((real_len > len) ? len : real_len);

	char	   *new = malloc(use_len + 1);

	if (new)
	{
		memcpy(new, str, use_len);
		new[use_len] = '\0';
	}
	else
		errno = ENOMEM;

	return new;
}