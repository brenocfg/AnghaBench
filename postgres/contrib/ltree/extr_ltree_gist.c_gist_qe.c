#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ltree_gist ;
struct TYPE_14__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ lquery_variant ;
struct TYPE_15__ {int numvar; } ;
typedef  TYPE_2__ lquery_level ;
struct TYPE_16__ {int numlevel; } ;
typedef  TYPE_3__ lquery ;
typedef  int /*<<< orphan*/  BITVECP ;

/* Variables and functions */
 scalar_t__ GETBIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASHVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ LQL_CANLOOKSIGN (TYPE_2__*) ; 
 TYPE_1__* LQL_FIRST (TYPE_2__*) ; 
 TYPE_2__* LQL_NEXT (TYPE_2__*) ; 
 TYPE_2__* LQUERY_FIRST (TYPE_3__*) ; 
 scalar_t__ LTG_ISALLTRUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LTG_SIGN (int /*<<< orphan*/ *) ; 
 TYPE_1__* LVAR_NEXT (TYPE_1__*) ; 

__attribute__((used)) static bool
gist_qe(ltree_gist *key, lquery *query)
{
	lquery_level *curq = LQUERY_FIRST(query);
	BITVECP		sign = LTG_SIGN(key);
	int			qlen = query->numlevel;

	if (LTG_ISALLTRUE(key))
		return true;

	while (qlen > 0)
	{
		if (curq->numvar && LQL_CANLOOKSIGN(curq))
		{
			bool		isexist = false;
			int			vlen = curq->numvar;
			lquery_variant *curv = LQL_FIRST(curq);

			while (vlen > 0)
			{
				if (GETBIT(sign, HASHVAL(curv->val)))
				{
					isexist = true;
					break;
				}
				curv = LVAR_NEXT(curv);
				vlen--;
			}
			if (!isexist)
				return false;
		}

		curq = LQL_NEXT(curq);
		qlen--;
	}

	return true;
}