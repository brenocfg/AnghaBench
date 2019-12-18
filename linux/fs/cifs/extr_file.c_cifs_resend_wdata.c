#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct cifs_credits {int dummy; } ;
struct cifs_writedata {unsigned int bytes; int /*<<< orphan*/  refcount; struct cifs_credits credits; int /*<<< orphan*/  list; TYPE_4__* cfile; } ;
struct cifs_aio_ctx {int dummy; } ;
struct TCP_Server_Info {TYPE_2__* ops; } ;
struct TYPE_8__ {scalar_t__ invalidHandle; int /*<<< orphan*/  tlink; } ;
struct TYPE_7__ {TYPE_1__* ses; } ;
struct TYPE_6__ {int (* wait_mtu_credits ) (struct TCP_Server_Info*,unsigned int,unsigned int*,struct cifs_credits*) ;int (* async_writev ) (struct cifs_writedata*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  add_credits_and_wake_if (struct TCP_Server_Info*,struct cifs_credits*,int /*<<< orphan*/ ) ; 
 int adjust_credits (struct TCP_Server_Info*,struct cifs_credits*,unsigned int) ; 
 int cifs_reopen_file (TYPE_4__*,int) ; 
 int /*<<< orphan*/  cifs_uncached_writedata_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct TCP_Server_Info*,unsigned int,unsigned int*,struct cifs_credits*) ; 
 int stub2 (struct cifs_writedata*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tlink_tcon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cifs_resend_wdata(struct cifs_writedata *wdata, struct list_head *wdata_list,
	struct cifs_aio_ctx *ctx)
{
	unsigned int wsize;
	struct cifs_credits credits;
	int rc;
	struct TCP_Server_Info *server =
		tlink_tcon(wdata->cfile->tlink)->ses->server;

	do {
		if (wdata->cfile->invalidHandle) {
			rc = cifs_reopen_file(wdata->cfile, false);
			if (rc == -EAGAIN)
				continue;
			else if (rc)
				break;
		}


		/*
		 * Wait for credits to resend this wdata.
		 * Note: we are attempting to resend the whole wdata not in
		 * segments
		 */
		do {
			rc = server->ops->wait_mtu_credits(server, wdata->bytes,
						&wsize, &credits);
			if (rc)
				goto fail;

			if (wsize < wdata->bytes) {
				add_credits_and_wake_if(server, &credits, 0);
				msleep(1000);
			}
		} while (wsize < wdata->bytes);
		wdata->credits = credits;

		rc = adjust_credits(server, &wdata->credits, wdata->bytes);

		if (!rc) {
			if (wdata->cfile->invalidHandle)
				rc = -EAGAIN;
			else
				rc = server->ops->async_writev(wdata,
					cifs_uncached_writedata_release);
		}

		/* If the write was successfully sent, we are done */
		if (!rc) {
			list_add_tail(&wdata->list, wdata_list);
			return 0;
		}

		/* Roll back credits and retry if needed */
		add_credits_and_wake_if(server, &wdata->credits, 0);
	} while (rc == -EAGAIN);

fail:
	kref_put(&wdata->refcount, cifs_uncached_writedata_release);
	return rc;
}