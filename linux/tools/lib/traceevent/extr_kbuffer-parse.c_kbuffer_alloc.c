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
struct kbuffer {int flags; int /*<<< orphan*/  next_event; int /*<<< orphan*/  read_long; int /*<<< orphan*/  read_4; int /*<<< orphan*/  read_8; } ;
typedef  enum kbuffer_long_size { ____Placeholder_kbuffer_long_size } kbuffer_long_size ;
typedef  enum kbuffer_endian { ____Placeholder_kbuffer_endian } kbuffer_endian ;

/* Variables and functions */
#define  KBUFFER_ENDIAN_BIG 131 
#define  KBUFFER_ENDIAN_LITTLE 130 
 int KBUFFER_FL_BIG_ENDIAN ; 
 int KBUFFER_FL_HOST_BIG_ENDIAN ; 
 int KBUFFER_FL_LONG_8 ; 
#define  KBUFFER_LSIZE_4 129 
#define  KBUFFER_LSIZE_8 128 
 int /*<<< orphan*/  __next_event ; 
 int /*<<< orphan*/  __read_4 ; 
 int /*<<< orphan*/  __read_4_sw ; 
 int /*<<< orphan*/  __read_8 ; 
 int /*<<< orphan*/  __read_8_sw ; 
 int /*<<< orphan*/  __read_long_4 ; 
 int /*<<< orphan*/  __read_long_8 ; 
 scalar_t__ do_swap (struct kbuffer*) ; 
 scalar_t__ host_is_bigendian () ; 
 struct kbuffer* zmalloc (int) ; 

struct kbuffer *
kbuffer_alloc(enum kbuffer_long_size size, enum kbuffer_endian endian)
{
	struct kbuffer *kbuf;
	int flags = 0;

	switch (size) {
	case KBUFFER_LSIZE_4:
		break;
	case KBUFFER_LSIZE_8:
		flags |= KBUFFER_FL_LONG_8;
		break;
	default:
		return NULL;
	}

	switch (endian) {
	case KBUFFER_ENDIAN_LITTLE:
		break;
	case KBUFFER_ENDIAN_BIG:
		flags |= KBUFFER_FL_BIG_ENDIAN;
		break;
	default:
		return NULL;
	}

	kbuf = zmalloc(sizeof(*kbuf));
	if (!kbuf)
		return NULL;

	kbuf->flags = flags;

	if (host_is_bigendian())
		kbuf->flags |= KBUFFER_FL_HOST_BIG_ENDIAN;

	if (do_swap(kbuf)) {
		kbuf->read_8 = __read_8_sw;
		kbuf->read_4 = __read_4_sw;
	} else {
		kbuf->read_8 = __read_8;
		kbuf->read_4 = __read_4;
	}

	if (kbuf->flags & KBUFFER_FL_LONG_8)
		kbuf->read_long = __read_long_8;
	else
		kbuf->read_long = __read_long_4;

	/* May be changed by kbuffer_set_old_format() */
	kbuf->next_event = __next_event;

	return kbuf;
}