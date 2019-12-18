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

/* Variables and functions */
 scalar_t__ BTF_KIND_ARRAY ; 
 scalar_t__ btf_kind (struct btf_type const*) ; 

__attribute__((used)) static inline bool btf_is_array(const struct btf_type *t)
{
	return btf_kind(t) == BTF_KIND_ARRAY;
}