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
typedef  int /*<<< orphan*/  u32 ;
struct btf {int dummy; } ;

/* Variables and functions */
 int __btf_name_valid (struct btf const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool btf_name_valid_identifier(const struct btf *btf, u32 offset)
{
	return __btf_name_valid(btf, offset, false);
}