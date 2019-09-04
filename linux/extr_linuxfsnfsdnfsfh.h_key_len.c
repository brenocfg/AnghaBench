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

/* Variables and functions */
#define  FSID_DEV 135 
#define  FSID_ENCODE_DEV 134 
#define  FSID_MAJOR_MINOR 133 
#define  FSID_NUM 132 
#define  FSID_UUID16 131 
#define  FSID_UUID16_INUM 130 
#define  FSID_UUID4_INUM 129 
#define  FSID_UUID8 128 

__attribute__((used)) static inline int key_len(int type)
{
	switch(type) {
	case FSID_DEV:		return 8;
	case FSID_NUM: 		return 4;
	case FSID_MAJOR_MINOR:	return 12;
	case FSID_ENCODE_DEV:	return 8;
	case FSID_UUID4_INUM:	return 8;
	case FSID_UUID8:	return 8;
	case FSID_UUID16:	return 16;
	case FSID_UUID16_INUM:	return 24;
	default: return 0;
	}
}