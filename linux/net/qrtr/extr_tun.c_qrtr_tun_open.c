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
struct TYPE_2__ {int /*<<< orphan*/  xmit; } ;
struct qrtr_tun {TYPE_1__ ep; int /*<<< orphan*/  readq; int /*<<< orphan*/  queue; } ;
struct inode {int dummy; } ;
struct file {struct qrtr_tun* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QRTR_EP_NID_AUTO ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct qrtr_tun* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qrtr_endpoint_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qrtr_tun_send ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qrtr_tun_open(struct inode *inode, struct file *filp)
{
	struct qrtr_tun *tun;

	tun = kzalloc(sizeof(*tun), GFP_KERNEL);
	if (!tun)
		return -ENOMEM;

	skb_queue_head_init(&tun->queue);
	init_waitqueue_head(&tun->readq);

	tun->ep.xmit = qrtr_tun_send;

	filp->private_data = tun;

	return qrtr_endpoint_register(&tun->ep, QRTR_EP_NID_AUTO);
}