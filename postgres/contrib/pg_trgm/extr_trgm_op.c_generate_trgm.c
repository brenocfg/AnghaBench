#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trgm ;
struct TYPE_5__ {int /*<<< orphan*/  flag; } ;
typedef  TYPE_1__ TRGM ;

/* Variables and functions */
 int /*<<< orphan*/  ARRKEY ; 
 int /*<<< orphan*/  CALCGTSIZE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ GETARR (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRGMHDRSIZE ; 
 int /*<<< orphan*/  comp_trgm ; 
 int generate_trgm_only (scalar_t__,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (scalar_t__) ; 
 int /*<<< orphan*/  protect_out_of_mem (int) ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 
 int qunique (scalar_t__,int,int,int /*<<< orphan*/ ) ; 

TRGM *
generate_trgm(char *str, int slen)
{
	TRGM	   *trg;
	int			len;

	protect_out_of_mem(slen);

	trg = (TRGM *) palloc(TRGMHDRSIZE + sizeof(trgm) * (slen / 2 + 1) * 3);
	trg->flag = ARRKEY;

	len = generate_trgm_only(GETARR(trg), str, slen, NULL);
	SET_VARSIZE(trg, CALCGTSIZE(ARRKEY, len));

	if (len == 0)
		return trg;

	/*
	 * Make trigrams unique.
	 */
	if (len > 1)
	{
		qsort((void *) GETARR(trg), len, sizeof(trgm), comp_trgm);
		len = qunique(GETARR(trg), len, sizeof(trgm), comp_trgm);
	}

	SET_VARSIZE(trg, CALCGTSIZE(ARRKEY, len));

	return trg;
}