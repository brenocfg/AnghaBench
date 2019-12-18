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
typedef  scalar_t__ SerializableXactHandle ;
typedef  int /*<<< orphan*/  SERIALIZABLEXACT ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CreateLocalPredicateLockHash () ; 
 int /*<<< orphan*/ * InvalidSerializableXact ; 
 int /*<<< orphan*/ * MySerializableXact ; 

void
AttachSerializableXact(SerializableXactHandle handle)
{

	Assert(MySerializableXact == InvalidSerializableXact);

	MySerializableXact = (SERIALIZABLEXACT *) handle;
	if (MySerializableXact != InvalidSerializableXact)
		CreateLocalPredicateLockHash();
}