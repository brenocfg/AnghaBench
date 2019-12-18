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
struct orangefs_khandle {int* u; } ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */

__attribute__((used)) static inline ino_t orangefs_khandle_to_ino(struct orangefs_khandle *khandle)
{
	union {
		unsigned char u[8];
		__u64 ino;
	} ihandle;

	ihandle.u[0] = khandle->u[0] ^ khandle->u[4];
	ihandle.u[1] = khandle->u[1] ^ khandle->u[5];
	ihandle.u[2] = khandle->u[2] ^ khandle->u[6];
	ihandle.u[3] = khandle->u[3] ^ khandle->u[7];
	ihandle.u[4] = khandle->u[12] ^ khandle->u[8];
	ihandle.u[5] = khandle->u[13] ^ khandle->u[9];
	ihandle.u[6] = khandle->u[14] ^ khandle->u[10];
	ihandle.u[7] = khandle->u[15] ^ khandle->u[11];

	return ihandle.ino;
}