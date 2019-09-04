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
typedef  scalar_t__ time64_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* cmp ) (struct key const*,TYPE_2__*) ;} ;
struct TYPE_3__ {scalar_t__ type; } ;
struct keyring_search_context {int flags; int skipped_ret; scalar_t__ now; int /*<<< orphan*/  possessed; void* result; int /*<<< orphan*/  cred; TYPE_2__ match_data; TYPE_1__ index_key; } ;
struct key {scalar_t__ type; int /*<<< orphan*/  expiry; int /*<<< orphan*/  serial; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 short EACCES ; 
 short EKEYEXPIRED ; 
 short EKEYREVOKED ; 
 void* ERR_PTR (short) ; 
 int KEYRING_SEARCH_DO_STATE_CHECK ; 
 int KEYRING_SEARCH_NO_CHECK_PERM ; 
 int KEYRING_SEARCH_SKIP_EXPIRED ; 
 int KEY_FLAG_INVALIDATED ; 
 int KEY_FLAG_REVOKED ; 
 int /*<<< orphan*/  KEY_NEED_SEARCH ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ key_task_permission (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct key* keyring_ptr_to_key (void const*) ; 
 int /*<<< orphan*/  kleave (char*,...) ; 
 void* make_key_ref (struct key const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct key const*,TYPE_2__*) ; 

__attribute__((used)) static int keyring_search_iterator(const void *object, void *iterator_data)
{
	struct keyring_search_context *ctx = iterator_data;
	const struct key *key = keyring_ptr_to_key(object);
	unsigned long kflags = READ_ONCE(key->flags);
	short state = READ_ONCE(key->state);

	kenter("{%d}", key->serial);

	/* ignore keys not of this type */
	if (key->type != ctx->index_key.type) {
		kleave(" = 0 [!type]");
		return 0;
	}

	/* skip invalidated, revoked and expired keys */
	if (ctx->flags & KEYRING_SEARCH_DO_STATE_CHECK) {
		time64_t expiry = READ_ONCE(key->expiry);

		if (kflags & ((1 << KEY_FLAG_INVALIDATED) |
			      (1 << KEY_FLAG_REVOKED))) {
			ctx->result = ERR_PTR(-EKEYREVOKED);
			kleave(" = %d [invrev]", ctx->skipped_ret);
			goto skipped;
		}

		if (expiry && ctx->now >= expiry) {
			if (!(ctx->flags & KEYRING_SEARCH_SKIP_EXPIRED))
				ctx->result = ERR_PTR(-EKEYEXPIRED);
			kleave(" = %d [expire]", ctx->skipped_ret);
			goto skipped;
		}
	}

	/* keys that don't match */
	if (!ctx->match_data.cmp(key, &ctx->match_data)) {
		kleave(" = 0 [!match]");
		return 0;
	}

	/* key must have search permissions */
	if (!(ctx->flags & KEYRING_SEARCH_NO_CHECK_PERM) &&
	    key_task_permission(make_key_ref(key, ctx->possessed),
				ctx->cred, KEY_NEED_SEARCH) < 0) {
		ctx->result = ERR_PTR(-EACCES);
		kleave(" = %d [!perm]", ctx->skipped_ret);
		goto skipped;
	}

	if (ctx->flags & KEYRING_SEARCH_DO_STATE_CHECK) {
		/* we set a different error code if we pass a negative key */
		if (state < 0) {
			ctx->result = ERR_PTR(state);
			kleave(" = %d [neg]", ctx->skipped_ret);
			goto skipped;
		}
	}

	/* Found */
	ctx->result = make_key_ref(key, ctx->possessed);
	kleave(" = 1 [found]");
	return 1;

skipped:
	return ctx->skipped_ret;
}