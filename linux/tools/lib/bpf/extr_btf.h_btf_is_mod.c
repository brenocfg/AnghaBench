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
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 scalar_t__ BTF_KIND_CONST ; 
 scalar_t__ BTF_KIND_RESTRICT ; 
 scalar_t__ BTF_KIND_VOLATILE ; 
 scalar_t__ btf_kind (struct btf_type const*) ; 

__attribute__((used)) static inline bool btf_is_mod(const struct btf_type *t)
{
	__u16 kind = btf_kind(t);

	return kind == BTF_KIND_VOLATILE ||
	       kind == BTF_KIND_CONST ||
	       kind == BTF_KIND_RESTRICT;
}