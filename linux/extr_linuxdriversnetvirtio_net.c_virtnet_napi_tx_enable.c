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
struct virtqueue {int dummy; } ;
struct virtnet_info {int /*<<< orphan*/  affinity_hint_set; } ;
struct napi_struct {scalar_t__ weight; } ;

/* Variables and functions */
 void virtnet_napi_enable (struct virtqueue*,struct napi_struct*) ; 

__attribute__((used)) static void virtnet_napi_tx_enable(struct virtnet_info *vi,
				   struct virtqueue *vq,
				   struct napi_struct *napi)
{
	if (!napi->weight)
		return;

	/* Tx napi touches cachelines on the cpu handling tx interrupts. Only
	 * enable the feature if this is likely affine with the transmit path.
	 */
	if (!vi->affinity_hint_set) {
		napi->weight = 0;
		return;
	}

	return virtnet_napi_enable(vq, napi);
}