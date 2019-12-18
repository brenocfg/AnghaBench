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
struct extent_changeset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  extent_changeset_release (struct extent_changeset*) ; 
 int /*<<< orphan*/  kfree (struct extent_changeset*) ; 

__attribute__((used)) static inline void extent_changeset_free(struct extent_changeset *changeset)
{
	if (!changeset)
		return;
	extent_changeset_release(changeset);
	kfree(changeset);
}