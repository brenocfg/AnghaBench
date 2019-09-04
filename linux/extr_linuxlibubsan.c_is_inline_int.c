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
struct type_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int type_bit_width (struct type_descriptor*) ; 
 int /*<<< orphan*/  type_is_int (struct type_descriptor*) ; 

__attribute__((used)) static bool is_inline_int(struct type_descriptor *type)
{
	unsigned inline_bits = sizeof(unsigned long)*8;
	unsigned bits = type_bit_width(type);

	WARN_ON(!type_is_int(type));

	return bits <= inline_bits;
}