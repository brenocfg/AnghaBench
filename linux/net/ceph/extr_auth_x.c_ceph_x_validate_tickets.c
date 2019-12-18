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
struct ceph_x_ticket_handler {int dummy; } ;
struct ceph_x_info {int have_keys; } ;
struct ceph_auth_client {int want_keys; struct ceph_x_info* private; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ceph_x_ticket_handler*) ; 
 struct ceph_x_ticket_handler* get_ticket_handler (struct ceph_auth_client*,int) ; 
 int /*<<< orphan*/  have_key (struct ceph_x_ticket_handler*) ; 
 scalar_t__ need_key (struct ceph_x_ticket_handler*) ; 

__attribute__((used)) static void ceph_x_validate_tickets(struct ceph_auth_client *ac, int *pneed)
{
	int want = ac->want_keys;
	struct ceph_x_info *xi = ac->private;
	int service;

	*pneed = ac->want_keys & ~(xi->have_keys);

	for (service = 1; service <= want; service <<= 1) {
		struct ceph_x_ticket_handler *th;

		if (!(ac->want_keys & service))
			continue;

		if (*pneed & service)
			continue;

		th = get_ticket_handler(ac, service);
		if (IS_ERR(th)) {
			*pneed |= service;
			continue;
		}

		if (need_key(th))
			*pneed |= service;
		if (!have_key(th))
			xi->have_keys &= ~service;
	}
}