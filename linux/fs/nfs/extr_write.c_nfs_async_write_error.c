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
struct nfs_page {int dummy; } ;
struct list_head {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 scalar_t__ nfs_error_is_fatal (int) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_redirty_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_write_error (struct nfs_page*,int) ; 

__attribute__((used)) static void nfs_async_write_error(struct list_head *head, int error)
{
	struct nfs_page	*req;

	while (!list_empty(head)) {
		req = nfs_list_entry(head->next);
		nfs_list_remove_request(req);
		if (nfs_error_is_fatal(error))
			nfs_write_error(req, error);
		else
			nfs_redirty_request(req);
	}
}