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
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_KIND_STRUCT ; 
 int /*<<< orphan*/  BTF_KIND_UNION ; 
 scalar_t__ btf_kflag (struct btf_type*) ; 

__attribute__((used)) static inline __u16 btf_fwd_kind(struct btf_type *t)
{
	return btf_kflag(t) ? BTF_KIND_UNION : BTF_KIND_STRUCT;
}