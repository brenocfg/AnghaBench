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
struct klp_shadow {unsigned long id; void* data; void* obj; int /*<<< orphan*/  node; } ;
typedef  int (* klp_shadow_ctor_t ) (void*,void*,void*) ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,void*,unsigned long) ; 
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct klp_shadow*) ; 
 void* klp_shadow_get (void*,unsigned long) ; 
 int /*<<< orphan*/  klp_shadow_hash ; 
 int /*<<< orphan*/  klp_shadow_lock ; 
 struct klp_shadow* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,void*,unsigned long,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (void*) ; 

__attribute__((used)) static void *__klp_shadow_get_or_alloc(void *obj, unsigned long id,
				       size_t size, gfp_t gfp_flags,
				       klp_shadow_ctor_t ctor, void *ctor_data,
				       bool warn_on_exist)
{
	struct klp_shadow *new_shadow;
	void *shadow_data;
	unsigned long flags;

	/* Check if the shadow variable already exists */
	shadow_data = klp_shadow_get(obj, id);
	if (shadow_data)
		goto exists;

	/*
	 * Allocate a new shadow variable.  Fill it with zeroes by default.
	 * More complex setting can be done by @ctor function.  But it is
	 * called only when the buffer is really used (under klp_shadow_lock).
	 */
	new_shadow = kzalloc(size + sizeof(*new_shadow), gfp_flags);
	if (!new_shadow)
		return NULL;

	/* Look for <obj, id> again under the lock */
	spin_lock_irqsave(&klp_shadow_lock, flags);
	shadow_data = klp_shadow_get(obj, id);
	if (unlikely(shadow_data)) {
		/*
		 * Shadow variable was found, throw away speculative
		 * allocation.
		 */
		spin_unlock_irqrestore(&klp_shadow_lock, flags);
		kfree(new_shadow);
		goto exists;
	}

	new_shadow->obj = obj;
	new_shadow->id = id;

	if (ctor) {
		int err;

		err = ctor(obj, new_shadow->data, ctor_data);
		if (err) {
			spin_unlock_irqrestore(&klp_shadow_lock, flags);
			kfree(new_shadow);
			pr_err("Failed to construct shadow variable <%p, %lx> (%d)\n",
			       obj, id, err);
			return NULL;
		}
	}

	/* No <obj, id> found, so attach the newly allocated one */
	hash_add_rcu(klp_shadow_hash, &new_shadow->node,
		     (unsigned long)new_shadow->obj);
	spin_unlock_irqrestore(&klp_shadow_lock, flags);

	return new_shadow->data;

exists:
	if (warn_on_exist) {
		WARN(1, "Duplicate shadow variable <%p, %lx>\n", obj, id);
		return NULL;
	}

	return shadow_data;
}