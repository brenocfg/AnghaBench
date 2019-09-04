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
struct cxgbi_sock {int dummy; } ;
struct cxgbi_ports_map {unsigned int max_connect; unsigned int sport_base; int /*<<< orphan*/  lock; int /*<<< orphan*/  port_csk; } ;
struct cxgbi_device {struct cxgbi_ports_map pmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cxgbi_alloc_big_mem (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,struct cxgbi_device*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int cxgbi_device_portmap_create(struct cxgbi_device *cdev, unsigned int base,
				unsigned int max_conn)
{
	struct cxgbi_ports_map *pmap = &cdev->pmap;

	pmap->port_csk = cxgbi_alloc_big_mem(max_conn *
					     sizeof(struct cxgbi_sock *),
					     GFP_KERNEL);
	if (!pmap->port_csk) {
		pr_warn("cdev 0x%p, portmap OOM %u.\n", cdev, max_conn);
		return -ENOMEM;
	}

	pmap->max_connect = max_conn;
	pmap->sport_base = base;
	spin_lock_init(&pmap->lock);
	return 0;
}