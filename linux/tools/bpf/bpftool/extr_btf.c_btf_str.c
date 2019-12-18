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
 scalar_t__ btf__name_by_offset (struct btf const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *btf_str(const struct btf *btf, __u32 off)
{
	if (!off)
		return "(anon)";
	return btf__name_by_offset(btf, off) ? : "(invalid)";
}