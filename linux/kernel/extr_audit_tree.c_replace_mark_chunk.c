#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fsnotify_mark {int dummy; } ;
struct audit_chunk {struct fsnotify_mark* mark; } ;
struct TYPE_2__ {struct audit_chunk* chunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 TYPE_1__* audit_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  hash_lock ; 
 struct audit_chunk* mark_chunk (struct fsnotify_mark*) ; 

__attribute__((used)) static void replace_mark_chunk(struct fsnotify_mark *mark,
			       struct audit_chunk *chunk)
{
	struct audit_chunk *old;

	assert_spin_locked(&hash_lock);
	old = mark_chunk(mark);
	audit_mark(mark)->chunk = chunk;
	if (chunk)
		chunk->mark = mark;
	if (old)
		old->mark = NULL;
}