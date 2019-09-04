#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct TYPE_6__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct dpni_rx_tc_dist_cfg {size_t num_extracts; int /*<<< orphan*/  key_cfg_iova; int /*<<< orphan*/  dist_mode; int /*<<< orphan*/  dist_size; struct dpkg_extract* extracts; } ;
struct dpkg_profile_cfg {size_t num_extracts; int /*<<< orphan*/  key_cfg_iova; int /*<<< orphan*/  dist_mode; int /*<<< orphan*/  dist_size; struct dpkg_extract* extracts; } ;
struct TYPE_7__ {int /*<<< orphan*/  field; int /*<<< orphan*/  type; int /*<<< orphan*/  prot; } ;
struct TYPE_8__ {TYPE_2__ from_hdr; } ;
struct dpkg_extract {TYPE_3__ extract; int /*<<< orphan*/  type; } ;
struct dpaa2_eth_priv {int rx_hash_fields; int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dist_cfg ;
typedef  int /*<<< orphan*/  cls_cfg ;
struct TYPE_9__ {int rxnfc_field; int /*<<< orphan*/  cls_field; int /*<<< orphan*/  cls_prot; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DPAA2_CLASSIFIER_DMA_SIZE ; 
 int /*<<< orphan*/  DPKG_EXTRACT_FROM_HDR ; 
 int /*<<< orphan*/  DPKG_FULL_FIELD ; 
 size_t DPKG_MAX_NUM_OF_EXTRACTS ; 
 int /*<<< orphan*/  DPNI_DIST_MODE_HASH ; 
 int E2BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_eth_hash_enabled (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  dpaa2_eth_queue_count (struct dpaa2_eth_priv*) ; 
 int dpni_prepare_key_cfg (struct dpni_rx_tc_dist_cfg*,int /*<<< orphan*/ *) ; 
 int dpni_set_rx_tc_dist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_rx_tc_dist_cfg*) ; 
 TYPE_4__* hash_fields ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dpni_rx_tc_dist_cfg*,int /*<<< orphan*/ ,int) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dpaa2_eth_set_hash(struct net_device *net_dev, u64 flags)
{
	struct device *dev = net_dev->dev.parent;
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	struct dpkg_profile_cfg cls_cfg;
	struct dpni_rx_tc_dist_cfg dist_cfg;
	u8 *dma_mem;
	int i;
	int err = 0;

	if (!dpaa2_eth_hash_enabled(priv)) {
		dev_dbg(dev, "Hashing support is not enabled\n");
		return 0;
	}

	memset(&cls_cfg, 0, sizeof(cls_cfg));

	for (i = 0; i < ARRAY_SIZE(hash_fields); i++) {
		struct dpkg_extract *key =
			&cls_cfg.extracts[cls_cfg.num_extracts];

		if (!(flags & hash_fields[i].rxnfc_field))
			continue;

		if (cls_cfg.num_extracts >= DPKG_MAX_NUM_OF_EXTRACTS) {
			dev_err(dev, "error adding key extraction rule, too many rules?\n");
			return -E2BIG;
		}

		key->type = DPKG_EXTRACT_FROM_HDR;
		key->extract.from_hdr.prot = hash_fields[i].cls_prot;
		key->extract.from_hdr.type = DPKG_FULL_FIELD;
		key->extract.from_hdr.field = hash_fields[i].cls_field;
		cls_cfg.num_extracts++;

		priv->rx_hash_fields |= hash_fields[i].rxnfc_field;
	}

	dma_mem = kzalloc(DPAA2_CLASSIFIER_DMA_SIZE, GFP_KERNEL);
	if (!dma_mem)
		return -ENOMEM;

	err = dpni_prepare_key_cfg(&cls_cfg, dma_mem);
	if (err) {
		dev_err(dev, "dpni_prepare_key_cfg error %d\n", err);
		goto err_prep_key;
	}

	memset(&dist_cfg, 0, sizeof(dist_cfg));

	/* Prepare for setting the rx dist */
	dist_cfg.key_cfg_iova = dma_map_single(dev, dma_mem,
					       DPAA2_CLASSIFIER_DMA_SIZE,
					       DMA_TO_DEVICE);
	if (dma_mapping_error(dev, dist_cfg.key_cfg_iova)) {
		dev_err(dev, "DMA mapping failed\n");
		err = -ENOMEM;
		goto err_dma_map;
	}

	dist_cfg.dist_size = dpaa2_eth_queue_count(priv);
	dist_cfg.dist_mode = DPNI_DIST_MODE_HASH;

	err = dpni_set_rx_tc_dist(priv->mc_io, 0, priv->mc_token, 0, &dist_cfg);
	dma_unmap_single(dev, dist_cfg.key_cfg_iova,
			 DPAA2_CLASSIFIER_DMA_SIZE, DMA_TO_DEVICE);
	if (err)
		dev_err(dev, "dpni_set_rx_tc_dist() error %d\n", err);

err_dma_map:
err_prep_key:
	kfree(dma_mem);
	return err;
}