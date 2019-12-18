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
typedef  int MultiXactOffset ;

/* Variables and functions */
 int MULTIXACT_MEMBERS_PER_PAGE ; 
 int MultiXactOffsetPrecedes (int,int) ; 

__attribute__((used)) static bool
MultiXactMemberPagePrecedes(int page1, int page2)
{
	MultiXactOffset offset1;
	MultiXactOffset offset2;

	offset1 = ((MultiXactOffset) page1) * MULTIXACT_MEMBERS_PER_PAGE;
	offset2 = ((MultiXactOffset) page2) * MULTIXACT_MEMBERS_PER_PAGE;

	return MultiXactOffsetPrecedes(offset1, offset2);
}