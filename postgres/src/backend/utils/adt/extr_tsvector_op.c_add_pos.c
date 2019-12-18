#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  WordEntryPos ;
struct TYPE_8__ {int haspos; } ;
typedef  TYPE_1__ WordEntry ;
struct TYPE_9__ {int npos; } ;
typedef  int /*<<< orphan*/  TSVector ;

/* Variables and functions */
 int /*<<< orphan*/  LIMITPOS (int) ; 
 int MAXENTRYPOS ; 
 int MAXNUMPOS ; 
 int POSDATALEN (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * POSDATAPTR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int WEP_GETPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEP_GETWEIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEP_SETPOS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEP_SETWEIGHT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* _POSVECPTR (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int32
add_pos(TSVector src, WordEntry *srcptr,
		TSVector dest, WordEntry *destptr,
		int32 maxpos)
{
	uint16	   *clen = &_POSVECPTR(dest, destptr)->npos;
	int			i;
	uint16		slen = POSDATALEN(src, srcptr),
				startlen;
	WordEntryPos *spos = POSDATAPTR(src, srcptr),
			   *dpos = POSDATAPTR(dest, destptr);

	if (!destptr->haspos)
		*clen = 0;

	startlen = *clen;
	for (i = 0;
		 i < slen && *clen < MAXNUMPOS &&
		 (*clen == 0 || WEP_GETPOS(dpos[*clen - 1]) != MAXENTRYPOS - 1);
		 i++)
	{
		WEP_SETWEIGHT(dpos[*clen], WEP_GETWEIGHT(spos[i]));
		WEP_SETPOS(dpos[*clen], LIMITPOS(WEP_GETPOS(spos[i]) + maxpos));
		(*clen)++;
	}

	if (*clen != startlen)
		destptr->haspos = 1;
	return *clen - startlen;
}