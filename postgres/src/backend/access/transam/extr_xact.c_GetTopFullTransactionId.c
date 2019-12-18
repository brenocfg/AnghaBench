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
typedef  int /*<<< orphan*/  FullTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  AssignTransactionId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FullTransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopTransactionStateData ; 
 int /*<<< orphan*/  XactTopFullTransactionId ; 

FullTransactionId
GetTopFullTransactionId(void)
{
	if (!FullTransactionIdIsValid(XactTopFullTransactionId))
		AssignTransactionId(&TopTransactionStateData);
	return XactTopFullTransactionId;
}