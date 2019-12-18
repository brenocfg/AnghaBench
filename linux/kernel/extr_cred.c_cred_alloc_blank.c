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
struct cred {int /*<<< orphan*/  magic; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRED_MAGIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cred_jar ; 
 struct cred* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ security_cred_alloc_blank (struct cred*,int /*<<< orphan*/ ) ; 

struct cred *cred_alloc_blank(void)
{
	struct cred *new;

	new = kmem_cache_zalloc(cred_jar, GFP_KERNEL);
	if (!new)
		return NULL;

	atomic_set(&new->usage, 1);
#ifdef CONFIG_DEBUG_CREDENTIALS
	new->magic = CRED_MAGIC;
#endif

	if (security_cred_alloc_blank(new, GFP_KERNEL) < 0)
		goto error;

	return new;

error:
	abort_creds(new);
	return NULL;
}