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
typedef  int /*<<< orphan*/  StringInfoData ;
typedef  scalar_t__ StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  initStringInfo (scalar_t__) ; 
 scalar_t__ palloc (int) ; 

StringInfo
makeStringInfo(void)
{
	StringInfo	res;

	res = (StringInfo) palloc(sizeof(StringInfoData));

	initStringInfo(res);

	return res;
}