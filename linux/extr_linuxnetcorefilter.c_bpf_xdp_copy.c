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
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned long) ; 

__attribute__((used)) static unsigned long bpf_xdp_copy(void *dst_buff, const void *src_buff,
				  unsigned long off, unsigned long len)
{
	memcpy(dst_buff, src_buff + off, len);
	return 0;
}