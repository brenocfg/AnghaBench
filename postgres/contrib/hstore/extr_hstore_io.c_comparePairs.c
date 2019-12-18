#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ keylen; scalar_t__ needfree; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Pairs ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
comparePairs(const void *a, const void *b)
{
	const Pairs *pa = a;
	const Pairs *pb = b;

	if (pa->keylen == pb->keylen)
	{
		int			res = memcmp(pa->key, pb->key, pa->keylen);

		if (res)
			return res;

		/* guarantee that needfree will be later */
		if (pb->needfree == pa->needfree)
			return 0;
		else if (pa->needfree)
			return 1;
		else
			return -1;
	}
	return (pa->keylen > pb->keylen) ? 1 : -1;
}