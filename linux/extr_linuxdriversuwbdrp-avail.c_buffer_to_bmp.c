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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 unsigned long get_val (int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static
void buffer_to_bmp(unsigned long *bmp_itr, void *_buffer,
		   size_t buffer_size)
{
	u8 *buffer = _buffer;
	size_t itr, len;
	unsigned long val;

	itr = 0;
	while (itr < buffer_size) {
		len = buffer_size - itr >= sizeof(val) ?
			sizeof(val) : buffer_size - itr;
		val = get_val(buffer, itr, len);
		bmp_itr[itr / sizeof(val)] = val;
		itr += sizeof(val);
	}
}