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
typedef  int ubyte ;
struct buffer_ext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_ext_add (struct buffer_ext*,int*,int) ; 

__attribute__((used)) static void emit_unsigned_LEB128(struct buffer_ext *be,
				 unsigned long data)
{
	do {
		ubyte cur = data & 0x7F;
		data >>= 7;
		if (data)
			cur |= 0x80;
		buffer_ext_add(be, &cur, 1);
	} while (data);
}