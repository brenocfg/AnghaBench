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
 int EINVAL ; 
 int errno ; 
 scalar_t__ isdigit (char) ; 
 size_t strcspn (char*,char const*) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 
 int /*<<< orphan*/  strtoull (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_num_or_str(char **inp, u64 *num, const char **str,
			    const char *str_delim)
{
	*inp += strspn(*inp, " ");

	if (isdigit(**inp)) {
		char *endptr;

		if (!num)
			return -EINVAL;
		errno = 0;
		*num = strtoull(*inp, &endptr, 0);
		if (errno)
			return -errno;
		if (endptr == *inp)
			return -EINVAL;
		*inp = endptr;
	} else {
		size_t n;

		if (!str)
			return -EINVAL;
		*inp += strspn(*inp, " ");
		*str = *inp;
		n = strcspn(*inp, str_delim);
		if (!n)
			return -EINVAL;
		*inp += n;
		if (**inp) {
			**inp = '\0';
			*inp += 1;
		}
	}
	return 0;
}