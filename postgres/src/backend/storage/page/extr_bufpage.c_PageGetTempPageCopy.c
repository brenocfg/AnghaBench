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
typedef  int /*<<< orphan*/  Size ;
typedef  scalar_t__ Page ;

/* Variables and functions */
 int /*<<< orphan*/  PageGetPageSize (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 

Page
PageGetTempPageCopy(Page page)
{
	Size		pageSize;
	Page		temp;

	pageSize = PageGetPageSize(page);
	temp = (Page) palloc(pageSize);

	memcpy(temp, page, pageSize);

	return temp;
}