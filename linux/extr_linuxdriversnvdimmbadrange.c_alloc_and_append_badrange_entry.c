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
typedef  int /*<<< orphan*/  u64 ;
struct badrange_entry {int dummy; } ;
struct badrange {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  append_badrange_entry (struct badrange*,struct badrange_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct badrange_entry* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_and_append_badrange_entry(struct badrange *badrange,
		u64 addr, u64 length, gfp_t flags)
{
	struct badrange_entry *bre;

	bre = kzalloc(sizeof(*bre), flags);
	if (!bre)
		return -ENOMEM;

	append_badrange_entry(badrange, bre, addr, length);
	return 0;
}