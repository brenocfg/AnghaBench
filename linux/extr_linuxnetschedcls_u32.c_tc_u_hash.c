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
struct tcf_proto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  U32_HASH_SHIFT ; 
 unsigned int hash_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_u_common_ptr (struct tcf_proto const*) ; 

__attribute__((used)) static unsigned int tc_u_hash(const struct tcf_proto *tp)
{
	return hash_ptr(tc_u_common_ptr(tp), U32_HASH_SHIFT);
}