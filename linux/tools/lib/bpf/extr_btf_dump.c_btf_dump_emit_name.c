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
struct btf_dump {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btf_dump_printf (struct btf_dump const*,char*,char*,char const*) ; 

__attribute__((used)) static void btf_dump_emit_name(const struct btf_dump *d,
			       const char *name, bool last_was_ptr)
{
	bool separate = name[0] && !last_was_ptr;

	btf_dump_printf(d, "%s%s", separate ? " " : "", name);
}