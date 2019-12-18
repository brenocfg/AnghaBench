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
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int __btf_dumper_type_only (struct btf const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

void btf_dumper_type_only(const struct btf *btf, __u32 type_id, char *func_sig,
			  int size)
{
	int err;

	func_sig[0] = '\0';
	if (!btf)
		return;

	err = __btf_dumper_type_only(btf, type_id, func_sig, 0, size);
	if (err < 0)
		func_sig[0] = '\0';
}