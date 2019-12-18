#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ owner; struct TYPE_5__* next; } ;
typedef  scalar_t__ ResourceReleasePhase ;
typedef  TYPE_1__ OSSLDigest ;

/* Variables and functions */
 scalar_t__ CurrentResourceOwner ; 
 scalar_t__ RESOURCE_RELEASE_AFTER_LOCKS ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  free_openssl_digest (TYPE_1__*) ; 
 TYPE_1__* open_digests ; 

__attribute__((used)) static void
digest_free_callback(ResourceReleasePhase phase,
					 bool isCommit,
					 bool isTopLevel,
					 void *arg)
{
	OSSLDigest *curr;
	OSSLDigest *next;

	if (phase != RESOURCE_RELEASE_AFTER_LOCKS)
		return;

	next = open_digests;
	while (next)
	{
		curr = next;
		next = curr->next;

		if (curr->owner == CurrentResourceOwner)
		{
			if (isCommit)
				elog(WARNING, "pgcrypto digest reference leak: digest %p still referenced", curr);
			free_openssl_digest(curr);
		}
	}
}