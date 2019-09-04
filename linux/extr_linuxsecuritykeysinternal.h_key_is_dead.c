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
struct key {int flags; scalar_t__ expiry; } ;

/* Variables and functions */
 int KEY_FLAG_DEAD ; 
 int KEY_FLAG_INVALIDATED ; 

__attribute__((used)) static inline bool key_is_dead(const struct key *key, time64_t limit)
{
	return
		key->flags & ((1 << KEY_FLAG_DEAD) |
			      (1 << KEY_FLAG_INVALIDATED)) ||
		(key->expiry > 0 && key->expiry <= limit);
}