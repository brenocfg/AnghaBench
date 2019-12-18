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
struct cache_detail {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_PENDING ; 
 int /*<<< orphan*/  cache_dequeue (struct cache_detail*,struct cache_head*) ; 
 int /*<<< orphan*/  cache_revisit_request (struct cache_head*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cache_fresh_unlocked(struct cache_head *head,
				 struct cache_detail *detail)
{
	if (test_and_clear_bit(CACHE_PENDING, &head->flags)) {
		cache_revisit_request(head);
		cache_dequeue(detail, head);
	}
}