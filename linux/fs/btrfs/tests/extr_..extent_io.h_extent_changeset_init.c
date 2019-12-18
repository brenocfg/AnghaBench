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
struct extent_changeset {int /*<<< orphan*/  range_changed; scalar_t__ bytes_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ulist_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void extent_changeset_init(struct extent_changeset *changeset)
{
	changeset->bytes_changed = 0;
	ulist_init(&changeset->range_changed);
}