#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lp; struct vio_dring_state* drings; } ;
struct vnet_port {int start_cons; TYPE_2__ vio; } ;
struct vio_net_dext {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct vio_net_desc {TYPE_1__ hdr; } ;
struct vio_dring_state {unsigned long entry_size; unsigned long num_entries; unsigned long pending; int ncookies; scalar_t__ cons; scalar_t__ prod; void* base; int /*<<< orphan*/  cookies; } ;
struct ldc_trans_cookie {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int LDC_MAP_DIRECT ; 
 int LDC_MAP_RW ; 
 int LDC_MAP_SHADOW ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  VIO_DESC_FREE ; 
 size_t VIO_DRIVER_TX_RING ; 
 int VIO_MAX_RING_COOKIES ; 
 unsigned long VNET_TX_RING_SIZE ; 
 void* ldc_alloc_exp_dring (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sunvnet_port_free_tx_bufs_common (struct vnet_port*) ; 
 struct vio_net_desc* vio_dring_entry (struct vio_dring_state*,int) ; 
 scalar_t__ vio_version_after_eq (TYPE_2__*,int,int) ; 

__attribute__((used)) static int vnet_port_alloc_tx_ring(struct vnet_port *port)
{
	struct vio_dring_state *dr;
	unsigned long len, elen;
	int i, err, ncookies;
	void *dring;

	dr = &port->vio.drings[VIO_DRIVER_TX_RING];

	elen = sizeof(struct vio_net_desc) +
	       sizeof(struct ldc_trans_cookie) * 2;
	if (vio_version_after_eq(&port->vio, 1, 7))
		elen += sizeof(struct vio_net_dext);
	len = VNET_TX_RING_SIZE * elen;

	ncookies = VIO_MAX_RING_COOKIES;
	dring = ldc_alloc_exp_dring(port->vio.lp, len,
				    dr->cookies, &ncookies,
				    (LDC_MAP_SHADOW |
				     LDC_MAP_DIRECT |
				     LDC_MAP_RW));
	if (IS_ERR(dring)) {
		err = PTR_ERR(dring);
		goto err_out;
	}

	dr->base = dring;
	dr->entry_size = elen;
	dr->num_entries = VNET_TX_RING_SIZE;
	dr->prod = 0;
	dr->cons = 0;
	port->start_cons  = true; /* need an initial trigger */
	dr->pending = VNET_TX_RING_SIZE;
	dr->ncookies = ncookies;

	for (i = 0; i < VNET_TX_RING_SIZE; ++i) {
		struct vio_net_desc *d;

		d = vio_dring_entry(dr, i);
		d->hdr.state = VIO_DESC_FREE;
	}
	return 0;

err_out:
	sunvnet_port_free_tx_bufs_common(port);

	return err;
}