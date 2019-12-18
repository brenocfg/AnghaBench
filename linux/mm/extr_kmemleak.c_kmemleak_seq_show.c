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
struct seq_file {int dummy; } ;
struct kmemleak_object {int flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int OBJECT_REPORTED ; 
 int /*<<< orphan*/  print_unreferenced (struct seq_file*,struct kmemleak_object*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unreferenced_object (struct kmemleak_object*) ; 

__attribute__((used)) static int kmemleak_seq_show(struct seq_file *seq, void *v)
{
	struct kmemleak_object *object = v;
	unsigned long flags;

	spin_lock_irqsave(&object->lock, flags);
	if ((object->flags & OBJECT_REPORTED) && unreferenced_object(object))
		print_unreferenced(seq, object);
	spin_unlock_irqrestore(&object->lock, flags);
	return 0;
}