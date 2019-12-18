#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ltree_level ;
typedef  int /*<<< orphan*/  ltree_gist ;
struct TYPE_9__ {int numlevel; } ;
typedef  TYPE_2__ ltree ;
typedef  int /*<<< orphan*/  BITVECP ;

/* Variables and functions */
 int /*<<< orphan*/  AHASHVAL (unsigned int) ; 
 int /*<<< orphan*/  GETBIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* LEVEL_NEXT (TYPE_1__*) ; 
 scalar_t__ LTG_ISALLTRUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LTG_SIGN (int /*<<< orphan*/ *) ; 
 TYPE_1__* LTREE_FIRST (TYPE_2__*) ; 
 unsigned int ltree_crc32_sz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
gist_te(ltree_gist *key, ltree *query)
{
	ltree_level *curq = LTREE_FIRST(query);
	BITVECP		sign = LTG_SIGN(key);
	int			qlen = query->numlevel;
	unsigned int hv;

	if (LTG_ISALLTRUE(key))
		return true;

	while (qlen > 0)
	{
		hv = ltree_crc32_sz(curq->name, curq->len);
		if (!GETBIT(sign, AHASHVAL(hv)))
			return false;
		curq = LEVEL_NEXT(curq);
		qlen--;
	}

	return true;
}