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
typedef  int /*<<< orphan*/  u16 ;
struct btf_type {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_INFO_VLEN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 btf_type_vlen(const struct btf_type *t)
{
	return BTF_INFO_VLEN(t->info);
}