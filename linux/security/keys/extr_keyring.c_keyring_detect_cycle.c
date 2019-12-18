#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lookup_type; struct key* raw_data; } ;
struct keyring_search_context {int flags; int /*<<< orphan*/  result; int /*<<< orphan*/  iterator; TYPE_1__ match_data; int /*<<< orphan*/  index_key; } ;
struct key {int /*<<< orphan*/  index_key; } ;

/* Variables and functions */
 int EAGAIN ; 
 int KEYRING_SEARCH_DETECT_TOO_DEEP ; 
 int /*<<< orphan*/  KEYRING_SEARCH_LOOKUP_DIRECT ; 
 int KEYRING_SEARCH_NO_CHECK_PERM ; 
 int KEYRING_SEARCH_NO_STATE_CHECK ; 
 int KEYRING_SEARCH_NO_UPDATE_TIME ; 
 int KEYRING_SEARCH_RECURSE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyring_detect_cycle_iterator ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  search_nested_keyrings (struct key*,struct keyring_search_context*) ; 

__attribute__((used)) static int keyring_detect_cycle(struct key *A, struct key *B)
{
	struct keyring_search_context ctx = {
		.index_key		= A->index_key,
		.match_data.raw_data	= A,
		.match_data.lookup_type = KEYRING_SEARCH_LOOKUP_DIRECT,
		.iterator		= keyring_detect_cycle_iterator,
		.flags			= (KEYRING_SEARCH_NO_STATE_CHECK |
					   KEYRING_SEARCH_NO_UPDATE_TIME |
					   KEYRING_SEARCH_NO_CHECK_PERM |
					   KEYRING_SEARCH_DETECT_TOO_DEEP |
					   KEYRING_SEARCH_RECURSE),
	};

	rcu_read_lock();
	search_nested_keyrings(B, &ctx);
	rcu_read_unlock();
	return PTR_ERR(ctx.result) == -EAGAIN ? 0 : PTR_ERR(ctx.result);
}