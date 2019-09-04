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
struct xdr_netobj {int data; int /*<<< orphan*/  len; } ;
struct kvec {int iov_len; int iov_base; } ;

/* Variables and functions */
 int round_up_to_quad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_getnl (struct kvec*) ; 

__attribute__((used)) static inline int
svc_safe_getnetobj(struct kvec *argv, struct xdr_netobj *o)
{
	int l;

	if (argv->iov_len < 4)
		return -1;
	o->len = svc_getnl(argv);
	l = round_up_to_quad(o->len);
	if (argv->iov_len < l)
		return -1;
	o->data = argv->iov_base;
	argv->iov_base += l;
	argv->iov_len -= l;
	return 0;
}