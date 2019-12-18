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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int KSTRTOX_OVERFLOW ; 
 unsigned int _parse_integer (char const*,int,unsigned long long*) ; 

__attribute__((used)) static const char *bitmap_getnum(const char *str, unsigned int *num)
{
	unsigned long long n;
	unsigned int len;

	len = _parse_integer(str, 10, &n);
	if (!len)
		return ERR_PTR(-EINVAL);
	if (len & KSTRTOX_OVERFLOW || n != (unsigned int)n)
		return ERR_PTR(-EOVERFLOW);

	*num = n;
	return str + len;
}