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
struct kbuffer_raw_info {unsigned int type; unsigned long long delta; int length; void* next; } ;
struct kbuffer {int flags; } ;

/* Variables and functions */
 unsigned int COMMIT_MASK ; 
 int KBUFFER_FL_LONG_8 ; 
 unsigned long long read_long (struct kbuffer*,void*) ; 
 unsigned int translate_data (struct kbuffer*,void*,void**,unsigned long long*,int*) ; 

struct kbuffer_raw_info *
kbuffer_raw_get(struct kbuffer *kbuf, void *subbuf, struct kbuffer_raw_info *info)
{
	unsigned long long flags;
	unsigned long long delta;
	unsigned int type_len;
	unsigned int size;
	int start;
	int length;
	void *ptr = info->next;

	if (!kbuf || !subbuf)
		return NULL;

	if (kbuf->flags & KBUFFER_FL_LONG_8)
		start = 16;
	else
		start = 12;

	flags = read_long(kbuf, subbuf + 8);
	size = (unsigned int)flags & COMMIT_MASK;

	if (ptr < subbuf || ptr >= subbuf + start + size)
		return NULL;

	type_len = translate_data(kbuf, ptr, &ptr, &delta, &length);

	info->next = ptr + length;

	info->type = type_len;
	info->delta = delta;
	info->length = length;

	return info;
}