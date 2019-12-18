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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AbortOutOfAnyTransaction () ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveTempRelations (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  myTempNamespace ; 

__attribute__((used)) static void
RemoveTempRelationsCallback(int code, Datum arg)
{
	if (OidIsValid(myTempNamespace))	/* should always be true */
	{
		/* Need to ensure we have a usable transaction. */
		AbortOutOfAnyTransaction();
		StartTransactionCommand();

		RemoveTempRelations(myTempNamespace);

		CommitTransactionCommand();
	}
}