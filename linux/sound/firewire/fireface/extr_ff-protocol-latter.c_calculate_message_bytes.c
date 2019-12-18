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
typedef  int u8 ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int calculate_message_bytes(u8 status)
{
	switch (status) {
	case 0xf6:	/* Tune request. */
	case 0xf8:	/* Timing clock. */
	case 0xfa:	/* Start. */
	case 0xfb:	/* Continue. */
	case 0xfc:	/* Stop. */
	case 0xfe:	/* Active sensing. */
	case 0xff:	/* System reset. */
		return 1;
	case 0xf1:	/* MIDI time code quarter frame. */
	case 0xf3:	/* Song select. */
		return 2;
	case 0xf2:	/* Song position pointer. */
		return 3;
	case 0xf0:	/* Exclusive. */
		return 0;
	case 0xf7:	/* End of exclusive. */
		break;
	case 0xf4:	/* Undefined. */
	case 0xf5:	/* Undefined. */
	case 0xf9:	/* Undefined. */
	case 0xfd:	/* Undefined. */
		break;
	default:
		switch (status & 0xf0) {
		case 0x80:	/* Note on. */
		case 0x90:	/* Note off. */
		case 0xa0:	/* Polyphonic key pressure. */
		case 0xb0:	/* Control change and Mode change. */
		case 0xe0:	/* Pitch bend change. */
			return 3;
		case 0xc0:	/* Program change. */
		case 0xd0:	/* Channel pressure. */
			return 2;
		default:
		break;
		}
	break;
	}

	return -EINVAL;
}