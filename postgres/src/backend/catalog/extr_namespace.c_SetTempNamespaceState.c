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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ InvalidSubTransactionId ; 
 int baseSearchPathValid ; 
 scalar_t__ myTempNamespace ; 
 scalar_t__ myTempNamespaceSubID ; 
 scalar_t__ myTempToastNamespace ; 

void
SetTempNamespaceState(Oid tempNamespaceId, Oid tempToastNamespaceId)
{
	/* Worker should not have created its own namespaces ... */
	Assert(myTempNamespace == InvalidOid);
	Assert(myTempToastNamespace == InvalidOid);
	Assert(myTempNamespaceSubID == InvalidSubTransactionId);

	/* Assign same namespace OIDs that leader has */
	myTempNamespace = tempNamespaceId;
	myTempToastNamespace = tempToastNamespaceId;

	/*
	 * It's fine to leave myTempNamespaceSubID == InvalidSubTransactionId.
	 * Even if the namespace is new so far as the leader is concerned, it's
	 * not new to the worker, and we certainly wouldn't want the worker trying
	 * to destroy it.
	 */

	baseSearchPathValid = false;	/* may need to rebuild list */
}