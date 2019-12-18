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
typedef  int /*<<< orphan*/  work_func_t ;
struct page {int dummy; } ;
struct cifs_writedata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct cifs_writedata* cifs_writedata_direct_alloc (struct page**,int /*<<< orphan*/ ) ; 
 struct page** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 

struct cifs_writedata *
cifs_writedata_alloc(unsigned int nr_pages, work_func_t complete)
{
	struct page **pages =
		kcalloc(nr_pages, sizeof(struct page *), GFP_NOFS);
	if (pages)
		return cifs_writedata_direct_alloc(pages, complete);

	return NULL;
}