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
struct apr_hdr {int pkt_size; int /*<<< orphan*/  dest_svc; int /*<<< orphan*/  dest_domain; int /*<<< orphan*/  src_svc; int /*<<< orphan*/  src_domain; } ;
struct apr_pkt {struct apr_hdr hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct apr_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  svc_id; int /*<<< orphan*/  domain_id; TYPE_1__ dev; } ;
struct apr {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_DOMAIN_APPS ; 
 struct apr* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int rpmsg_trysend (int /*<<< orphan*/ ,struct apr_pkt*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int apr_send_pkt(struct apr_device *adev, struct apr_pkt *pkt)
{
	struct apr *apr = dev_get_drvdata(adev->dev.parent);
	struct apr_hdr *hdr;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&adev->lock, flags);

	hdr = &pkt->hdr;
	hdr->src_domain = APR_DOMAIN_APPS;
	hdr->src_svc = adev->svc_id;
	hdr->dest_domain = adev->domain_id;
	hdr->dest_svc = adev->svc_id;

	ret = rpmsg_trysend(apr->ch, pkt, hdr->pkt_size);
	spin_unlock_irqrestore(&adev->lock, flags);

	return ret ? ret : hdr->pkt_size;
}