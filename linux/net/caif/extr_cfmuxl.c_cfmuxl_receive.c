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
typedef  int /*<<< orphan*/  u8 ;
struct cfpkt {int dummy; } ;
struct cfmuxl {int dummy; } ;
struct cflayer {int (* receive ) (struct cflayer*,struct cfpkt*) ;} ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 scalar_t__ cfpkt_extr_head (struct cfpkt*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cfsrvl_get (struct cflayer*) ; 
 int /*<<< orphan*/  cfsrvl_put (struct cflayer*) ; 
 struct cfmuxl* container_obj (struct cflayer*) ; 
 struct cflayer* get_up (struct cfmuxl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (struct cflayer*,struct cfpkt*) ; 

__attribute__((used)) static int cfmuxl_receive(struct cflayer *layr, struct cfpkt *pkt)
{
	int ret;
	struct cfmuxl *muxl = container_obj(layr);
	u8 id;
	struct cflayer *up;
	if (cfpkt_extr_head(pkt, &id, 1) < 0) {
		pr_err("erroneous Caif Packet\n");
		cfpkt_destroy(pkt);
		return -EPROTO;
	}
	rcu_read_lock();
	up = get_up(muxl, id);

	if (up == NULL) {
		pr_debug("Received data on unknown link ID = %d (0x%x)"
			" up == NULL", id, id);
		cfpkt_destroy(pkt);
		/*
		 * Don't return ERROR, since modem misbehaves and sends out
		 * flow on before linksetup response.
		 */

		rcu_read_unlock();
		return /* CFGLU_EPROT; */ 0;
	}

	/* We can't hold rcu_lock during receive, so take a ref count instead */
	cfsrvl_get(up);
	rcu_read_unlock();

	ret = up->receive(up, pkt);

	cfsrvl_put(up);
	return ret;
}