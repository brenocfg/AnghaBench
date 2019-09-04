#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  page; } ;
typedef  TYPE_1__ nfs_readdir_descriptor_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_page_release (TYPE_1__*) ; 
 int /*<<< orphan*/  get_cache_page (TYPE_1__*) ; 
 int nfs_readdir_search_array (TYPE_1__*) ; 

__attribute__((used)) static
int find_cache_page(nfs_readdir_descriptor_t *desc)
{
	int res;

	desc->page = get_cache_page(desc);
	if (IS_ERR(desc->page))
		return PTR_ERR(desc->page);

	res = nfs_readdir_search_array(desc);
	if (res != 0)
		cache_page_release(desc);
	return res;
}