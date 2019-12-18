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
struct hashmap {int dummy; } ;
struct btf_dump {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap__find (struct hashmap*,char const*,void**) ; 
 int /*<<< orphan*/  hashmap__set (struct hashmap*,char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t btf_dump_name_dups(struct btf_dump *d, struct hashmap *name_map,
				 const char *orig_name)
{
	size_t dup_cnt = 0;

	hashmap__find(name_map, orig_name, (void **)&dup_cnt);
	dup_cnt++;
	hashmap__set(name_map, orig_name, (void *)dup_cnt, NULL, NULL);

	return dup_cnt;
}