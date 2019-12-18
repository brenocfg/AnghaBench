#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ page_index; scalar_t__ last_cookie; scalar_t__ current_index; } ;
typedef  TYPE_1__ nfs_readdir_descriptor_t ;

/* Variables and functions */
 int EAGAIN ; 
 int find_cache_page (TYPE_1__*) ; 

__attribute__((used)) static inline
int readdir_search_pagecache(nfs_readdir_descriptor_t *desc)
{
	int res;

	if (desc->page_index == 0) {
		desc->current_index = 0;
		desc->last_cookie = 0;
	}
	do {
		res = find_cache_page(desc);
	} while (res == -EAGAIN);
	return res;
}