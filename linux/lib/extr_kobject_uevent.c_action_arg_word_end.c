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
 int /*<<< orphan*/  isalnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *action_arg_word_end(const char *buf, const char *buf_end,
				       char delim)
{
	const char *next = buf;

	while (next <= buf_end && *next != delim)
		if (!isalnum(*next++))
			return NULL;

	if (next == buf)
		return NULL;

	return next;
}