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
typedef  int uint32 ;
typedef  int MultiXactOffset ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAX_MEMBERS_IN_LAST_MEMBERS_PAGE ; 
 int MULTIXACT_MEMBERS_PER_PAGE ; 
 int MXOffsetToFlagsBitShift (int) ; 
 int MXOffsetToFlagsOffset (int) ; 
 int MXOffsetToMemberPage (int) ; 
 int MaxMultiXactOffset ; 
 int /*<<< orphan*/  MultiXactMemberControlLock ; 
 int /*<<< orphan*/  ZeroMultiXactMemberPage (int,int) ; 

__attribute__((used)) static void
ExtendMultiXactMember(MultiXactOffset offset, int nmembers)
{
	/*
	 * It's possible that the members span more than one page of the members
	 * file, so we loop to ensure we consider each page.  The coding is not
	 * optimal if the members span several pages, but that seems unusual
	 * enough to not worry much about.
	 */
	while (nmembers > 0)
	{
		int			flagsoff;
		int			flagsbit;
		uint32		difference;

		/*
		 * Only zero when at first entry of a page.
		 */
		flagsoff = MXOffsetToFlagsOffset(offset);
		flagsbit = MXOffsetToFlagsBitShift(offset);
		if (flagsoff == 0 && flagsbit == 0)
		{
			int			pageno;

			pageno = MXOffsetToMemberPage(offset);

			LWLockAcquire(MultiXactMemberControlLock, LW_EXCLUSIVE);

			/* Zero the page and make an XLOG entry about it */
			ZeroMultiXactMemberPage(pageno, true);

			LWLockRelease(MultiXactMemberControlLock);
		}

		/*
		 * Compute the number of items till end of current page.  Careful: if
		 * addition of unsigned ints wraps around, we're at the last page of
		 * the last segment; since that page holds a different number of items
		 * than other pages, we need to do it differently.
		 */
		if (offset + MAX_MEMBERS_IN_LAST_MEMBERS_PAGE < offset)
		{
			/*
			 * This is the last page of the last segment; we can compute the
			 * number of items left to allocate in it without modulo
			 * arithmetic.
			 */
			difference = MaxMultiXactOffset - offset + 1;
		}
		else
			difference = MULTIXACT_MEMBERS_PER_PAGE - offset % MULTIXACT_MEMBERS_PER_PAGE;

		/*
		 * Advance to next page, taking care to properly handle the wraparound
		 * case.  OK if nmembers goes negative.
		 */
		nmembers -= difference;
		offset += difference;
	}
}