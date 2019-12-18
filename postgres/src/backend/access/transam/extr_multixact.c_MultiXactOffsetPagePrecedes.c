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
typedef  int MultiXactId ;

/* Variables and functions */
 scalar_t__ FirstMultiXactId ; 
 int MULTIXACT_OFFSETS_PER_PAGE ; 
 int MultiXactIdPrecedes (int,int) ; 

__attribute__((used)) static bool
MultiXactOffsetPagePrecedes(int page1, int page2)
{
	MultiXactId multi1;
	MultiXactId multi2;

	multi1 = ((MultiXactId) page1) * MULTIXACT_OFFSETS_PER_PAGE;
	multi1 += FirstMultiXactId;
	multi2 = ((MultiXactId) page2) * MULTIXACT_OFFSETS_PER_PAGE;
	multi2 += FirstMultiXactId;

	return MultiXactIdPrecedes(multi1, multi2);
}