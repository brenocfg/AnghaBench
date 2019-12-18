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
 int /*<<< orphan*/  ISSJISHEAD (unsigned char) ; 
 int /*<<< orphan*/  ISSJISTAIL (unsigned char) ; 
 int pg_sjis_mblen (unsigned char const*) ; 

__attribute__((used)) static int
pg_sjis_verifier(const unsigned char *s, int len)
{
	int			l,
				mbl;
	unsigned char c1,
				c2;

	l = mbl = pg_sjis_mblen(s);

	if (len < l)
		return -1;

	if (l == 1)					/* pg_sjis_mblen already verified it */
		return mbl;

	c1 = *s++;
	c2 = *s;
	if (!ISSJISHEAD(c1) || !ISSJISTAIL(c2))
		return -1;
	return mbl;
}