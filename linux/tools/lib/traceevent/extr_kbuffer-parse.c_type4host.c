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
struct kbuffer {int flags; } ;

/* Variables and functions */
 int KBUFFER_FL_BIG_ENDIAN ; 

__attribute__((used)) static unsigned int type4host(struct kbuffer *kbuf,
			      unsigned int type_len_ts)
{
	if (kbuf->flags & KBUFFER_FL_BIG_ENDIAN)
		return (type_len_ts >> 29) & 3;
	else
		return type_len_ts & 3;
}