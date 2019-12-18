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
struct kbuffer {int curr; int next; int size; int index; unsigned int timestamp; void* data; } ;

/* Variables and functions */
#define  OLD_RINGBUF_TYPE_PADDING 130 
#define  OLD_RINGBUF_TYPE_TIME_EXTEND 129 
#define  OLD_RINGBUF_TYPE_TIME_STAMP 128 
 unsigned long long TS_SHIFT ; 
 int calc_index (struct kbuffer*,void*) ; 
 unsigned int len4host (struct kbuffer*,unsigned int) ; 
 void* read_4 (struct kbuffer*,void*) ; 
 unsigned int ts4host (struct kbuffer*,unsigned int) ; 
 unsigned int type4host (struct kbuffer*,unsigned int) ; 

__attribute__((used)) static unsigned int old_update_pointers(struct kbuffer *kbuf)
{
	unsigned long long extend;
	unsigned int type_len_ts;
	unsigned int type;
	unsigned int len;
	unsigned int delta;
	unsigned int length;
	void *ptr = kbuf->data + kbuf->curr;

	type_len_ts = read_4(kbuf, ptr);
	ptr += 4;

	type = type4host(kbuf, type_len_ts);
	len = len4host(kbuf, type_len_ts);
	delta = ts4host(kbuf, type_len_ts);

	switch (type) {
	case OLD_RINGBUF_TYPE_PADDING:
		kbuf->next = kbuf->size;
		return 0;

	case OLD_RINGBUF_TYPE_TIME_EXTEND:
		extend = read_4(kbuf, ptr);
		extend <<= TS_SHIFT;
		extend += delta;
		delta = extend;
		ptr += 4;
		length = 0;
		break;

	case OLD_RINGBUF_TYPE_TIME_STAMP:
		/* should never happen! */
		kbuf->curr = kbuf->size;
		kbuf->next = kbuf->size;
		kbuf->index = kbuf->size;
		return -1;
	default:
		if (len)
			length = len * 4;
		else {
			length = read_4(kbuf, ptr);
			length -= 4;
			ptr += 4;
		}
		break;
	}

	kbuf->timestamp += delta;
	kbuf->index = calc_index(kbuf, ptr);
	kbuf->next = kbuf->index + length;

	return type;
}