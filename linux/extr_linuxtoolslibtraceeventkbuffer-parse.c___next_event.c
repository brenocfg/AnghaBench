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
struct kbuffer {scalar_t__ curr; scalar_t__ next; scalar_t__ size; } ;

/* Variables and functions */
 int KBUFFER_TYPE_PADDING ; 
 int KBUFFER_TYPE_TIME_EXTEND ; 
 int update_pointers (struct kbuffer*) ; 

__attribute__((used)) static int __next_event(struct kbuffer *kbuf)
{
	int type;

	do {
		kbuf->curr = kbuf->next;
		if (kbuf->next >= kbuf->size)
			return -1;
		type = update_pointers(kbuf);
	} while (type == KBUFFER_TYPE_TIME_EXTEND || type == KBUFFER_TYPE_PADDING);

	return 0;
}