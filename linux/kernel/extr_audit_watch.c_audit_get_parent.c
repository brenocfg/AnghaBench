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
struct audit_parent {int /*<<< orphan*/  mark; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsnotify_get_mark (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (struct audit_parent*) ; 

__attribute__((used)) static void audit_get_parent(struct audit_parent *parent)
{
	if (likely(parent))
		fsnotify_get_mark(&parent->mark);
}