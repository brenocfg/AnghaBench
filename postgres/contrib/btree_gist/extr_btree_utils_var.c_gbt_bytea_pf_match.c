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
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  gbtree_vinfo ;
typedef  int /*<<< orphan*/  bytea ;

/* Variables and functions */
 char* VARDATA (int /*<<< orphan*/  const*) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARSIZE (int /*<<< orphan*/  const*) ; 
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 

__attribute__((used)) static bool
gbt_bytea_pf_match(const bytea *pf, const bytea *query, const gbtree_vinfo *tinfo)
{
	bool		out = false;
	int32		qlen = VARSIZE(query) - VARHDRSZ;
	int32		nlen = VARSIZE(pf) - VARHDRSZ;

	if (nlen <= qlen)
	{
		char	   *q = VARDATA(query);
		char	   *n = VARDATA(pf);

		out = (memcmp(q, n, nlen) == 0);
	}

	return out;
}