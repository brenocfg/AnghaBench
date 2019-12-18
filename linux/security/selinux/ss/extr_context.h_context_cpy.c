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
struct context {int /*<<< orphan*/ * str; scalar_t__ len; int /*<<< orphan*/  type; int /*<<< orphan*/  role; int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mls_context_cpy (struct context*,struct context*) ; 

__attribute__((used)) static inline int context_cpy(struct context *dst, struct context *src)
{
	int rc;

	dst->user = src->user;
	dst->role = src->role;
	dst->type = src->type;
	if (src->str) {
		dst->str = kstrdup(src->str, GFP_ATOMIC);
		if (!dst->str)
			return -ENOMEM;
		dst->len = src->len;
	} else {
		dst->str = NULL;
		dst->len = 0;
	}
	rc = mls_context_cpy(dst, src);
	if (rc) {
		kfree(dst->str);
		return rc;
	}
	return 0;
}