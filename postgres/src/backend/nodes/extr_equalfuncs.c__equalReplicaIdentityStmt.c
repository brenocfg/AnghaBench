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
typedef  int /*<<< orphan*/  ReplicaIdentityStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identity_type ; 
 int /*<<< orphan*/  name ; 

__attribute__((used)) static bool
_equalReplicaIdentityStmt(const ReplicaIdentityStmt *a, const ReplicaIdentityStmt *b)
{
	COMPARE_SCALAR_FIELD(identity_type);
	COMPARE_STRING_FIELD(name);

	return true;
}