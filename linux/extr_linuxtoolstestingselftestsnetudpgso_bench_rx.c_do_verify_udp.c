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
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int sanitized_char (char const) ; 

__attribute__((used)) static void do_verify_udp(const char *data, int len)
{
	char cur = data[0];
	int i;

	/* verify contents */
	if (cur < 'a' || cur > 'z')
		error(1, 0, "data initial byte out of range");

	for (i = 1; i < len; i++) {
		if (cur == 'z')
			cur = 'a';
		else
			cur++;

		if (data[i] != cur)
			error(1, 0, "data[%d]: len %d, %c(%hhu) != %c(%hhu)\n",
			      i, len,
			      sanitized_char(data[i]), data[i],
			      sanitized_char(cur), cur);
	}
}