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
typedef  int /*<<< orphan*/  user_data ;
struct socket {struct sock* sk; } ;
struct sockaddr_iucv {int /*<<< orphan*/  siucv_user_id; int /*<<< orphan*/  siucv_name; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct iucv_sock {int /*<<< orphan*/ * path; int /*<<< orphan*/  msglimit; int /*<<< orphan*/  src_name; } ;
struct TYPE_2__ {int (* path_connect ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (unsigned char*,int) ; 
 int EACCES ; 
 int EAGAIN ; 
 int ECONNREFUSED ; 
 int ENETUNREACH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IUCV_IPRMDATA ; 
 int /*<<< orphan*/  af_iucv_handler ; 
 int /*<<< orphan*/  high_nmcpy (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iucv_path_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_path_free (int /*<<< orphan*/ *) ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  low_nmcpy (unsigned char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pr_iucv ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,struct sock*) ; 

__attribute__((used)) static int afiucv_path_connect(struct socket *sock, struct sockaddr *addr)
{
	struct sockaddr_iucv *sa = (struct sockaddr_iucv *) addr;
	struct sock *sk = sock->sk;
	struct iucv_sock *iucv = iucv_sk(sk);
	unsigned char user_data[16];
	int err;

	high_nmcpy(user_data, sa->siucv_name);
	low_nmcpy(user_data, iucv->src_name);
	ASCEBC(user_data, sizeof(user_data));

	/* Create path. */
	iucv->path = iucv_path_alloc(iucv->msglimit,
				     IUCV_IPRMDATA, GFP_KERNEL);
	if (!iucv->path) {
		err = -ENOMEM;
		goto done;
	}
	err = pr_iucv->path_connect(iucv->path, &af_iucv_handler,
				    sa->siucv_user_id, NULL, user_data,
				    sk);
	if (err) {
		iucv_path_free(iucv->path);
		iucv->path = NULL;
		switch (err) {
		case 0x0b:	/* Target communicator is not logged on */
			err = -ENETUNREACH;
			break;
		case 0x0d:	/* Max connections for this guest exceeded */
		case 0x0e:	/* Max connections for target guest exceeded */
			err = -EAGAIN;
			break;
		case 0x0f:	/* Missing IUCV authorization */
			err = -EACCES;
			break;
		default:
			err = -ECONNREFUSED;
			break;
		}
	}
done:
	return err;
}