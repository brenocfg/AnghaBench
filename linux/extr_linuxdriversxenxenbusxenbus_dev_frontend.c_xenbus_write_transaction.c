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
struct xsd_sockmsg {scalar_t__ tx_id; int len; } ;
struct xenbus_transaction_holder {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {scalar_t__ buffer; } ;
struct xenbus_file_priv {int /*<<< orphan*/  transactions; TYPE_1__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XS_ERROR ; 
 unsigned int XS_TRANSACTION_END ; 
 unsigned int XS_TRANSACTION_START ; 
 int /*<<< orphan*/  kfree (struct xenbus_transaction_holder*) ; 
 struct xenbus_transaction_holder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int xenbus_command_reply (struct xenbus_file_priv*,int /*<<< orphan*/ ,char*) ; 
 int xenbus_dev_request_and_reply (struct xsd_sockmsg*,struct xenbus_file_priv*) ; 
 int /*<<< orphan*/  xenbus_get_transaction (struct xenbus_file_priv*,scalar_t__) ; 

__attribute__((used)) static int xenbus_write_transaction(unsigned msg_type,
				    struct xenbus_file_priv *u)
{
	int rc;
	struct xenbus_transaction_holder *trans = NULL;
	struct {
		struct xsd_sockmsg hdr;
		char body[];
	} *msg = (void *)u->u.buffer;

	if (msg_type == XS_TRANSACTION_START) {
		trans = kzalloc(sizeof(*trans), GFP_KERNEL);
		if (!trans) {
			rc = -ENOMEM;
			goto out;
		}
		list_add(&trans->list, &u->transactions);
	} else if (msg->hdr.tx_id != 0 &&
		   !xenbus_get_transaction(u, msg->hdr.tx_id))
		return xenbus_command_reply(u, XS_ERROR, "ENOENT");
	else if (msg_type == XS_TRANSACTION_END &&
		 !(msg->hdr.len == 2 &&
		   (!strcmp(msg->body, "T") || !strcmp(msg->body, "F"))))
		return xenbus_command_reply(u, XS_ERROR, "EINVAL");

	rc = xenbus_dev_request_and_reply(&msg->hdr, u);
	if (rc && trans) {
		list_del(&trans->list);
		kfree(trans);
	}

out:
	return rc;
}