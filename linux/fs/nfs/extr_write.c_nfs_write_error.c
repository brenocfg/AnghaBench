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
struct nfs_page {int /*<<< orphan*/  wb_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_end_page_writeback (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_inode_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_mapping_set_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_set_pageerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_file_mapping (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_write_error(struct nfs_page *req, int error)
{
	nfs_set_pageerror(page_file_mapping(req->wb_page));
	nfs_mapping_set_error(req->wb_page, error);
	nfs_inode_remove_request(req);
	nfs_end_page_writeback(req);
	nfs_release_request(req);
}