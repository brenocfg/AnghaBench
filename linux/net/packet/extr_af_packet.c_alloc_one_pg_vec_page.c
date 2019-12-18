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
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_COMP ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,unsigned long) ; 
 int /*<<< orphan*/  array_size (int,int /*<<< orphan*/ ) ; 
 char* vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *alloc_one_pg_vec_page(unsigned long order)
{
	char *buffer;
	gfp_t gfp_flags = GFP_KERNEL | __GFP_COMP |
			  __GFP_ZERO | __GFP_NOWARN | __GFP_NORETRY;

	buffer = (char *) __get_free_pages(gfp_flags, order);
	if (buffer)
		return buffer;

	/* __get_free_pages failed, fall back to vmalloc */
	buffer = vzalloc(array_size((1 << order), PAGE_SIZE));
	if (buffer)
		return buffer;

	/* vmalloc failed, lets dig into swap here */
	gfp_flags &= ~__GFP_NORETRY;
	buffer = (char *) __get_free_pages(gfp_flags, order);
	if (buffer)
		return buffer;

	/* complete and utter failure */
	return NULL;
}