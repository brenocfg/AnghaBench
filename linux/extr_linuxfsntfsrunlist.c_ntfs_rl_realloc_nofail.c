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
typedef  int /*<<< orphan*/  runlist_element ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_ALIGN (int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntfs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ntfs_malloc_nofs_nofail (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline runlist_element *ntfs_rl_realloc_nofail(runlist_element *rl,
		int old_size, int new_size)
{
	runlist_element *new_rl;

	old_size = PAGE_ALIGN(old_size * sizeof(*rl));
	new_size = PAGE_ALIGN(new_size * sizeof(*rl));
	if (old_size == new_size)
		return rl;

	new_rl = ntfs_malloc_nofs_nofail(new_size);
	BUG_ON(!new_rl);

	if (likely(rl != NULL)) {
		if (unlikely(old_size > new_size))
			old_size = new_size;
		memcpy(new_rl, rl, old_size);
		ntfs_free(rl);
	}
	return new_rl;
}