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
typedef  int /*<<< orphan*/  u8 ;
struct cfpkt {int dummy; } ;
struct cfmuxl {int dummy; } ;
struct cflayer {int (* transmit ) (struct cflayer*,struct cfpkt*) ;} ;
struct caif_payload_info {int hdr_len; int /*<<< orphan*/  channel_id; TYPE_1__* dev_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  cffrml_hold (struct cflayer*) ; 
 int /*<<< orphan*/  cffrml_put (struct cflayer*) ; 
 int /*<<< orphan*/  cfpkt_add_head (struct cfpkt*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 struct caif_payload_info* cfpkt_info (struct cfpkt*) ; 
 struct cfmuxl* container_obj (struct cflayer*) ; 
 struct cflayer* get_dn (struct cfmuxl*,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (struct cflayer*,struct cfpkt*) ; 

__attribute__((used)) static int cfmuxl_transmit(struct cflayer *layr, struct cfpkt *pkt)
{
	struct cfmuxl *muxl = container_obj(layr);
	int err;
	u8 linkid;
	struct cflayer *dn;
	struct caif_payload_info *info = cfpkt_info(pkt);
	BUG_ON(!info);

	rcu_read_lock();

	dn = get_dn(muxl, info->dev_info);
	if (dn == NULL) {
		pr_debug("Send data on unknown phy ID = %d (0x%x)\n",
			info->dev_info->id, info->dev_info->id);
		rcu_read_unlock();
		cfpkt_destroy(pkt);
		return -ENOTCONN;
	}

	info->hdr_len += 1;
	linkid = info->channel_id;
	cfpkt_add_head(pkt, &linkid, 1);

	/* We can't hold rcu_lock during receive, so take a ref count instead */
	cffrml_hold(dn);

	rcu_read_unlock();

	err = dn->transmit(dn, pkt);

	cffrml_put(dn);
	return err;
}