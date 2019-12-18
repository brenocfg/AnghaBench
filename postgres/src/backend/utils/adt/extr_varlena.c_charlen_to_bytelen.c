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
 int pg_database_encoding_max_length () ; 
 int /*<<< orphan*/  pg_mblen (char const*) ; 

__attribute__((used)) static int
charlen_to_bytelen(const char *p, int n)
{
	if (pg_database_encoding_max_length() == 1)
	{
		/* Optimization for single-byte encodings */
		return n;
	}
	else
	{
		const char *s;

		for (s = p; n > 0; n--)
			s += pg_mblen(s);

		return s - p;
	}
}