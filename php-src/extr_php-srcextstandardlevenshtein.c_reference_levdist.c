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
typedef  size_t zend_long ;

/* Variables and functions */
 size_t LEVENSHTEIN_MAX_LENGTH ; 
 int /*<<< orphan*/  efree (size_t*) ; 
 size_t* safe_emalloc (size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_long reference_levdist(const char *s1, size_t l1, const char *s2, size_t l2, zend_long cost_ins, zend_long cost_rep, zend_long cost_del )
{
	zend_long *p1, *p2, *tmp;
	zend_long c0, c1, c2;
	size_t i1, i2;

	if (l1 == 0) {
		return l2 * cost_ins;
	}
	if (l2 == 0) {
		return l1 * cost_del;
	}

	if ((l1 > LEVENSHTEIN_MAX_LENGTH) || (l2 > LEVENSHTEIN_MAX_LENGTH)) {
		return -1;
	}
	p1 = safe_emalloc((l2 + 1), sizeof(zend_long), 0);
	p2 = safe_emalloc((l2 + 1), sizeof(zend_long), 0);

	for (i2 = 0; i2 <= l2; i2++) {
		p1[i2] = i2 * cost_ins;
	}
	for (i1 = 0; i1 < l1 ; i1++) {
		p2[0] = p1[0] + cost_del;

		for (i2 = 0; i2 < l2; i2++) {
			c0 = p1[i2] + ((s1[i1] == s2[i2]) ? 0 : cost_rep);
			c1 = p1[i2 + 1] + cost_del;
			if (c1 < c0) {
				c0 = c1;
			}
			c2 = p2[i2] + cost_ins;
			if (c2 < c0) {
				c0 = c2;
			}
			p2[i2 + 1] = c0;
		}
		tmp = p1;
		p1 = p2;
		p2 = tmp;
	}
	c0 = p1[l2];

	efree(p1);
	efree(p2);

	return c0;
}