#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ (* cmp ) (struct key*,TYPE_1__*) ;} ;
struct keyring_search_context {TYPE_1__ match_data; } ;
struct key {int flags; } ;
struct TYPE_4__ {struct key* cached_requested_key; } ;

/* Variables and functions */
 int KEY_FLAG_INVALIDATED ; 
 int KEY_FLAG_REVOKED ; 
 TYPE_2__* current ; 
 struct key* key_get (struct key*) ; 
 scalar_t__ stub1 (struct key*,TYPE_1__*) ; 

__attribute__((used)) static struct key *check_cached_key(struct keyring_search_context *ctx)
{
#ifdef CONFIG_KEYS_REQUEST_CACHE
	struct key *key = current->cached_requested_key;

	if (key &&
	    ctx->match_data.cmp(key, &ctx->match_data) &&
	    !(key->flags & ((1 << KEY_FLAG_INVALIDATED) |
			    (1 << KEY_FLAG_REVOKED))))
		return key_get(key);
#endif
	return NULL;
}