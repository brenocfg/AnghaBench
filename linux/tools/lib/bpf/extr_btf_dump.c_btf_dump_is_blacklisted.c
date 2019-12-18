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
struct btf_type {scalar_t__ name_off; } ;
struct btf_dump {int /*<<< orphan*/  btf; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_name_of (struct btf_dump*,scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool btf_dump_is_blacklisted(struct btf_dump *d, __u32 id)
{
	const struct btf_type *t = btf__type_by_id(d->btf, id);

	/* __builtin_va_list is a compiler built-in, which causes compilation
	 * errors, when compiling w/ different compiler, then used to compile
	 * original code (e.g., GCC to compile kernel, Clang to use generated
	 * C header from BTF). As it is built-in, it should be already defined
	 * properly internally in compiler.
	 */
	if (t->name_off == 0)
		return false;
	return strcmp(btf_name_of(d, t->name_off), "__builtin_va_list") == 0;
}