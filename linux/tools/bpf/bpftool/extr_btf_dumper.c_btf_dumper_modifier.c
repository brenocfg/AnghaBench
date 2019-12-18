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
struct btf_dumper {int /*<<< orphan*/  btf; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int btf__resolve_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btf_dumper_do_type (struct btf_dumper const*,int,int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static int btf_dumper_modifier(const struct btf_dumper *d, __u32 type_id,
			       __u8 bit_offset, const void *data)
{
	int actual_type_id;

	actual_type_id = btf__resolve_type(d->btf, type_id);
	if (actual_type_id < 0)
		return actual_type_id;

	return btf_dumper_do_type(d, actual_type_id, bit_offset, data);
}