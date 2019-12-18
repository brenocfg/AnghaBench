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
struct cache_head {int /*<<< orphan*/  flags; } ;
struct cache_detail {int /*<<< orphan*/  hash_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NEGATIVE ; 
 scalar_t__ CACHE_NEW_EXPIRY ; 
 int EAGAIN ; 
 int ENOENT ; 
 int /*<<< orphan*/  cache_fresh_locked (struct cache_head*,scalar_t__,struct cache_detail*) ; 
 int /*<<< orphan*/  cache_fresh_unlocked (struct cache_head*,struct cache_detail*) ; 
 int cache_is_valid (struct cache_head*) ; 
 scalar_t__ seconds_since_boot () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int try_to_negate_entry(struct cache_detail *detail, struct cache_head *h)
{
	int rv;

	spin_lock(&detail->hash_lock);
	rv = cache_is_valid(h);
	if (rv == -EAGAIN) {
		set_bit(CACHE_NEGATIVE, &h->flags);
		cache_fresh_locked(h, seconds_since_boot()+CACHE_NEW_EXPIRY,
				   detail);
		rv = -ENOENT;
	}
	spin_unlock(&detail->hash_lock);
	cache_fresh_unlocked(h, detail);
	return rv;
}