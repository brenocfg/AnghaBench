#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_pageio_descriptor {int /*<<< orphan*/  pg_error; TYPE_1__* pg_completion_ops; } ;
struct nfs_page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* error_cleanup ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  nfs_list_move_request (struct nfs_page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfs_pageio_cleanup_request(struct nfs_pageio_descriptor *desc,
		struct nfs_page *req)
{
	LIST_HEAD(head);

	nfs_list_move_request(req, &head);
	desc->pg_completion_ops->error_cleanup(&head, desc->pg_error);
}