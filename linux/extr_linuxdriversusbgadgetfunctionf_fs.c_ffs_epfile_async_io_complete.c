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
struct usb_request {struct ffs_io_data* context; } ;
struct usb_ep {int dummy; } ;
struct ffs_io_data {int /*<<< orphan*/  work; struct ffs_data* ffs; } ;
struct ffs_data {int /*<<< orphan*/  io_completion_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffs_user_copy_worker ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffs_epfile_async_io_complete(struct usb_ep *_ep,
					 struct usb_request *req)
{
	struct ffs_io_data *io_data = req->context;
	struct ffs_data *ffs = io_data->ffs;

	ENTER();

	INIT_WORK(&io_data->work, ffs_user_copy_worker);
	queue_work(ffs->io_completion_wq, &io_data->work);
}