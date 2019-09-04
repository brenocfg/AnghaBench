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
struct vsock_sock {struct hvsock* trans; } ;
struct hvsock {struct vsock_sock* vsk; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hvsock* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hvs_sock_init(struct vsock_sock *vsk, struct vsock_sock *psk)
{
	struct hvsock *hvs;

	hvs = kzalloc(sizeof(*hvs), GFP_KERNEL);
	if (!hvs)
		return -ENOMEM;

	vsk->trans = hvs;
	hvs->vsk = vsk;

	return 0;
}