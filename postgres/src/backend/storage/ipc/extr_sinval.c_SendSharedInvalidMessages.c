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
typedef  int /*<<< orphan*/  SharedInvalidationMessage ;

/* Variables and functions */
 int /*<<< orphan*/  SIInsertDataEntries (int /*<<< orphan*/  const*,int) ; 

void
SendSharedInvalidMessages(const SharedInvalidationMessage *msgs, int n)
{
	SIInsertDataEntries(msgs, n);
}