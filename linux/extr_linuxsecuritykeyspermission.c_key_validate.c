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
typedef  scalar_t__ time64_t ;
struct key {int /*<<< orphan*/  expiry; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EKEYEXPIRED ; 
 int EKEYREVOKED ; 
 int ENOKEY ; 
 int KEY_FLAG_DEAD ; 
 int KEY_FLAG_INVALIDATED ; 
 int KEY_FLAG_REVOKED ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get_real_seconds () ; 

int key_validate(const struct key *key)
{
	unsigned long flags = READ_ONCE(key->flags);
	time64_t expiry = READ_ONCE(key->expiry);

	if (flags & (1 << KEY_FLAG_INVALIDATED))
		return -ENOKEY;

	/* check it's still accessible */
	if (flags & ((1 << KEY_FLAG_REVOKED) |
		     (1 << KEY_FLAG_DEAD)))
		return -EKEYREVOKED;

	/* check it hasn't expired */
	if (expiry) {
		if (ktime_get_real_seconds() >= expiry)
			return -EKEYEXPIRED;
	}

	return 0;
}