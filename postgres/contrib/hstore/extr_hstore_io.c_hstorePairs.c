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
typedef  int /*<<< orphan*/  Pairs ;
typedef  int /*<<< orphan*/  HStore ;
typedef  int /*<<< orphan*/  HEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * ARRPTR (int /*<<< orphan*/ *) ; 
 scalar_t__ CALCDATASIZE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HS_ADDITEM (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HS_FINALIZE (int /*<<< orphan*/ *,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  HS_SETCOUNT (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 char* STRPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * palloc (scalar_t__) ; 

HStore *
hstorePairs(Pairs *pairs, int32 pcount, int32 buflen)
{
	HStore	   *out;
	HEntry	   *entry;
	char	   *ptr;
	char	   *buf;
	int32		len;
	int32		i;

	len = CALCDATASIZE(pcount, buflen);
	out = palloc(len);
	SET_VARSIZE(out, len);
	HS_SETCOUNT(out, pcount);

	if (pcount == 0)
		return out;

	entry = ARRPTR(out);
	buf = ptr = STRPTR(out);

	for (i = 0; i < pcount; i++)
		HS_ADDITEM(entry, buf, ptr, pairs[i]);

	HS_FINALIZE(out, pcount, buf, ptr);

	return out;
}