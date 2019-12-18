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
struct counted_str {char* name; int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct counted_str* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

char *aa_str_alloc(int size, gfp_t gfp)
{
	struct counted_str *str;

	str = kmalloc(sizeof(struct counted_str) + size, gfp);
	if (!str)
		return NULL;

	kref_init(&str->count);
	return str->name;
}