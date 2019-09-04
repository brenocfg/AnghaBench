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
struct qstr {char* name; int len; } ;

/* Variables and functions */

unsigned name_to_int(const struct qstr *qstr)
{
	const char *name = qstr->name;
	int len = qstr->len;
	unsigned n = 0;

	if (len > 1 && *name == '0')
		goto out;
	do {
		unsigned c = *name++ - '0';
		if (c > 9)
			goto out;
		if (n >= (~0U-9)/10)
			goto out;
		n *= 10;
		n += c;
	} while (--len > 0);
	return n;
out:
	return ~0U;
}