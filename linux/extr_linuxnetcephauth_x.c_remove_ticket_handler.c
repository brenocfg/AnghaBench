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
struct ceph_x_ticket_handler {scalar_t__ ticket_blob; int /*<<< orphan*/  session_key; int /*<<< orphan*/  node; int /*<<< orphan*/  service; } ;
struct ceph_x_info {int /*<<< orphan*/  ticket_handlers; } ;
struct ceph_auth_client {struct ceph_x_info* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_buffer_put (scalar_t__) ; 
 int /*<<< orphan*/  ceph_crypto_key_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_x_ticket_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ceph_x_ticket_handler*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_ticket_handler(struct ceph_auth_client *ac,
				  struct ceph_x_ticket_handler *th)
{
	struct ceph_x_info *xi = ac->private;

	dout("remove_ticket_handler %p %d\n", th, th->service);
	rb_erase(&th->node, &xi->ticket_handlers);
	ceph_crypto_key_destroy(&th->session_key);
	if (th->ticket_blob)
		ceph_buffer_put(th->ticket_blob);
	kfree(th);
}