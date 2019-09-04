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
struct cxgbi_sock {int /*<<< orphan*/  lock; } ;
struct cxgbi_ports_map {int max_connect; struct cxgbi_sock** port_csk; } ;
struct cxgbi_device {struct cxgbi_ports_map pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_OFFLOAD_DOWN ; 
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  cxgbi_sock_closed (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_set_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,struct cxgbi_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void cxgbi_device_portmap_cleanup(struct cxgbi_device *cdev)
{
	struct cxgbi_ports_map *pmap = &cdev->pmap;
	struct cxgbi_sock *csk;
	int i;

	for (i = 0; i < pmap->max_connect; i++) {
		if (pmap->port_csk[i]) {
			csk = pmap->port_csk[i];
			pmap->port_csk[i] = NULL;
			log_debug(1 << CXGBI_DBG_SOCK,
				"csk 0x%p, cdev 0x%p, offload down.\n",
				csk, cdev);
			spin_lock_bh(&csk->lock);
			cxgbi_sock_set_flag(csk, CTPF_OFFLOAD_DOWN);
			cxgbi_sock_closed(csk);
			spin_unlock_bh(&csk->lock);
			cxgbi_sock_put(csk);
		}
	}
}