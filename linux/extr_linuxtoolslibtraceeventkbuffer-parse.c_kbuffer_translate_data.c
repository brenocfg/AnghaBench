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
struct kbuffer {void* flags; int /*<<< orphan*/  read_4; int /*<<< orphan*/  read_8; } ;

/* Variables and functions */
 void* KBUFFER_FL_BIG_ENDIAN ; 
#define  KBUFFER_TYPE_PADDING 130 
#define  KBUFFER_TYPE_TIME_EXTEND 129 
#define  KBUFFER_TYPE_TIME_STAMP 128 
 int /*<<< orphan*/  __read_4 ; 
 int /*<<< orphan*/  __read_4_sw ; 
 int /*<<< orphan*/  __read_8 ; 
 int /*<<< orphan*/  __read_8_sw ; 
 scalar_t__ host_is_bigendian () ; 
 int translate_data (struct kbuffer*,void*,void**,unsigned long long*,int*) ; 

void *kbuffer_translate_data(int swap, void *data, unsigned int *size)
{
	unsigned long long delta;
	struct kbuffer kbuf;
	int type_len;
	int length;
	void *ptr;

	if (swap) {
		kbuf.read_8 = __read_8_sw;
		kbuf.read_4 = __read_4_sw;
		kbuf.flags = host_is_bigendian() ? 0 : KBUFFER_FL_BIG_ENDIAN;
	} else {
		kbuf.read_8 = __read_8;
		kbuf.read_4 = __read_4;
		kbuf.flags = host_is_bigendian() ? KBUFFER_FL_BIG_ENDIAN: 0;
	}

	type_len = translate_data(&kbuf, data, &ptr, &delta, &length);
	switch (type_len) {
	case KBUFFER_TYPE_PADDING:
	case KBUFFER_TYPE_TIME_EXTEND:
	case KBUFFER_TYPE_TIME_STAMP:
		return NULL;
	};

	*size = length;

	return ptr;
}