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
struct btf_array {int /*<<< orphan*/  nelems; int /*<<< orphan*/  index_type; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 struct btf_array* btf_array (struct btf_type*) ; 
 long btf_hash_common (struct btf_type*) ; 
 long hash_combine (long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long btf_hash_array(struct btf_type *t)
{
	const struct btf_array *info = btf_array(t);
	long h = btf_hash_common(t);

	h = hash_combine(h, info->type);
	h = hash_combine(h, info->index_type);
	h = hash_combine(h, info->nelems);
	return h;
}