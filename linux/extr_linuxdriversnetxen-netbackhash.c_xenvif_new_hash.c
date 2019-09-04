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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
struct xenvif {TYPE_1__ hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  xen_netif_toeplitz_hash (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  xenvif_add_hash (struct xenvif*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ xenvif_hash_cache_size ; 

__attribute__((used)) static u32 xenvif_new_hash(struct xenvif *vif, const u8 *data,
			   unsigned int len)
{
	u32 val;

	val = xen_netif_toeplitz_hash(vif->hash.key,
				      sizeof(vif->hash.key),
				      data, len);

	if (xenvif_hash_cache_size != 0)
		xenvif_add_hash(vif, data, len, val);

	return val;
}