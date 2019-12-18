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
struct bitmask {unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  _setbit (struct bitmask*,unsigned int,int) ; 
 int /*<<< orphan*/  bitmask_clearall (struct bitmask*) ; 
 char* nexttoken (char const*,char) ; 
 int /*<<< orphan*/  scan_was_ok (int,char,char*) ; 
 int sscanf (char const*,char*,unsigned int*,char*) ; 

int bitmask_parselist(const char *buf, struct bitmask *bmp)
{
	const char *p, *q;

	bitmask_clearall(bmp);

	q = buf;
	while (p = q, q = nexttoken(q, ','), p) {
		unsigned int a;		/* begin of range */
		unsigned int b;		/* end of range */
		unsigned int s;		/* stride */
		const char *c1, *c2;	/* next tokens after '-' or ',' */
		char nextc;		/* char after sscanf %u match */
		int sret;		/* sscanf return (number of matches) */

		sret = sscanf(p, "%u%c", &a, &nextc);
		if (!scan_was_ok(sret, nextc, ",-"))
			goto err;
		b = a;
		s = 1;
		c1 = nexttoken(p, '-');
		c2 = nexttoken(p, ',');
		if (c1 != NULL && (c2 == NULL || c1 < c2)) {
			sret = sscanf(c1, "%u%c", &b, &nextc);
			if (!scan_was_ok(sret, nextc, ",:"))
				goto err;
			c1 = nexttoken(c1, ':');
			if (c1 != NULL && (c2 == NULL || c1 < c2)) {
				sret = sscanf(c1, "%u%c", &s, &nextc);
				if (!scan_was_ok(sret, nextc, ","))
					goto err;
			}
		}
		if (!(a <= b))
			goto err;
		if (b >= bmp->size)
			goto err;
		while (a <= b) {
			_setbit(bmp, a, 1);
			a += s;
		}
	}
	return 0;
err:
	bitmask_clearall(bmp);
	return -1;
}