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
struct btf_type {int dummy; } ;
struct btf_dump {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  btf_dump_printf (struct btf_dump*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_dump_type_name (struct btf_dump*,int /*<<< orphan*/ ) ; 
 scalar_t__ btf_is_struct (struct btf_type const*) ; 

__attribute__((used)) static void btf_dump_emit_struct_fwd(struct btf_dump *d, __u32 id,
				     const struct btf_type *t)
{
	btf_dump_printf(d, "%s %s",
			btf_is_struct(t) ? "struct" : "union",
			btf_dump_type_name(d, id));
}