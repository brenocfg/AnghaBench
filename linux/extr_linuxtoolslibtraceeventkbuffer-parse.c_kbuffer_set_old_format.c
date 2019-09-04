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
struct kbuffer {int /*<<< orphan*/  next_event; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUFFER_FL_OLD_FORMAT ; 
 int /*<<< orphan*/  __old_next_event ; 

void kbuffer_set_old_format(struct kbuffer *kbuf)
{
	kbuf->flags |= KBUFFER_FL_OLD_FORMAT;

	kbuf->next_event = __old_next_event;
}