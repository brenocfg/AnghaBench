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
typedef  int /*<<< orphan*/  seen ;

/* Variables and functions */
 int hash_len ; 
 int /*<<< orphan*/  hash_prefix ; 
 int /*<<< orphan*/  hash_prefix_len ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_prefixed_hash(const char *str)
{
	const char *end;
	bool seen[16];
	size_t i;
	int count;

	if (strncmp(str, hash_prefix, hash_prefix_len))
		return false;
	str += hash_prefix_len;

	memset(seen, false, sizeof(seen));
	for (end = str + hash_len; str < end; str++)
		if (*str >= '0' && *str <= '9')
			seen[*str - '0'] = true;
		else if (*str >= 'a' && *str <= 'f')
			seen[*str - 'a' + 10] = true;
		else
			return false;

	/* Count how many distinct digits seen */
	count = 0;
	for (i = 0; i < 16; i++)
		if (seen[i])
			count++;

	return count >= 5 && count <= 15;
}