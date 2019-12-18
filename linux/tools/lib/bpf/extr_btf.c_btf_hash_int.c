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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 long btf_hash_common (struct btf_type*) ; 
 long hash_combine (long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long btf_hash_int(struct btf_type *t)
{
	__u32 info = *(__u32 *)(t + 1);
	long h;

	h = btf_hash_common(t);
	h = hash_combine(h, info);
	return h;
}