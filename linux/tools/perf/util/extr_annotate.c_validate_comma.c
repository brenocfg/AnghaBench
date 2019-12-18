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
struct ins_operands {char const* raw_comment; } ;

/* Variables and functions */

__attribute__((used)) static inline const char *validate_comma(const char *c, struct ins_operands *ops)
{
	if (ops->raw_comment && c > ops->raw_comment)
		return NULL;

	return c;
}