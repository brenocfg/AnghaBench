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
struct TYPE_2__ {struct key const* raw_data; } ;
struct keyring_search_context {int /*<<< orphan*/  result; TYPE_1__ match_data; } ;
struct key {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDEADLK ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 struct key* keyring_ptr_to_key (void const*) ; 

__attribute__((used)) static int keyring_detect_cycle_iterator(const void *object,
					 void *iterator_data)
{
	struct keyring_search_context *ctx = iterator_data;
	const struct key *key = keyring_ptr_to_key(object);

	kenter("{%d}", key->serial);

	/* We might get a keyring with matching index-key that is nonetheless a
	 * different keyring. */
	if (key != ctx->match_data.raw_data)
		return 0;

	ctx->result = ERR_PTR(-EDEADLK);
	return 1;
}