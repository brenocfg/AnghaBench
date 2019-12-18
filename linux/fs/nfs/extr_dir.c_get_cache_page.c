#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  page_index; TYPE_1__* file; } ;
typedef  TYPE_2__ nfs_readdir_descriptor_t ;
struct TYPE_5__ {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_readdir_filler ; 
 struct page* read_cache_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static
struct page *get_cache_page(nfs_readdir_descriptor_t *desc)
{
	return read_cache_page(desc->file->f_mapping, desc->page_index,
			nfs_readdir_filler, desc);
}