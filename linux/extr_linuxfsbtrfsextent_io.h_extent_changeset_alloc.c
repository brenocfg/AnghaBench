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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  extent_changeset_init (struct extent_changeset*) ; 
 struct extent_changeset* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct extent_changeset *extent_changeset_alloc(void)
{
	struct extent_changeset *ret;

	ret = kmalloc(sizeof(*ret), GFP_KERNEL);
	if (!ret)
		return NULL;

	extent_changeset_init(ret);
	return ret;
}