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
typedef  int /*<<< orphan*/  ubyte ;
struct buffer_ext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_ext_add (struct buffer_ext*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emit_unsigned_LEB128 (struct buffer_ext*,unsigned long) ; 

__attribute__((used)) static void emit_opcode_unsigned(struct buffer_ext *be, ubyte opcode,
				 unsigned long data)
{
	buffer_ext_add(be, &opcode, 1);
	emit_unsigned_LEB128(be, data);
}