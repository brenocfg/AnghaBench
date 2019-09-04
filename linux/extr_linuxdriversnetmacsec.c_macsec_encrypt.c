#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {size_t len; int /*<<< orphan*/  dev; } ;
struct scatterlist {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  OutPktsTooLong; } ;
struct pcpu_secy_stats {int /*<<< orphan*/  syncp; TYPE_2__ stats; } ;
struct net_device {int dummy; } ;
struct macsec_tx_sc {size_t encoding_sa; scalar_t__ encrypt; int /*<<< orphan*/ * sa; } ;
struct TYPE_7__ {int /*<<< orphan*/  tfm; } ;
struct macsec_tx_sa {TYPE_3__ key; } ;
struct macsec_secy {int operational; int icv_len; int /*<<< orphan*/  sci; struct macsec_tx_sc tx_sc; } ;
struct macsec_eth_header {int dummy; } ;
struct macsec_dev {int /*<<< orphan*/  stats; TYPE_1__* real_dev; struct macsec_secy secy; } ;
struct ethhdr {int dummy; } ;
struct aead_request {int dummy; } ;
struct TYPE_8__ {struct macsec_tx_sa* tx_sa; struct aead_request* req; } ;
struct TYPE_5__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOLINK ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MACSEC_NEEDED_HEADROOM ; 
 scalar_t__ MACSEC_NEEDED_TAILROOM ; 
 int /*<<< orphan*/  aead_request_free (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,struct scatterlist*,struct scatterlist*,int,unsigned char*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 struct aead_request* macsec_alloc_req (int /*<<< orphan*/ ,unsigned char**,struct scatterlist**,int) ; 
 int /*<<< orphan*/  macsec_encrypt_done ; 
 int /*<<< orphan*/  macsec_extra_len (int) ; 
 int /*<<< orphan*/  macsec_fill_iv (unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  macsec_fill_sectag (struct macsec_eth_header*,struct macsec_secy*,scalar_t__,int) ; 
 int macsec_hdr_len (int) ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 
 int /*<<< orphan*/  macsec_set_shortlen (struct macsec_eth_header*,size_t) ; 
 TYPE_4__* macsec_skb_cb (struct sk_buff*) ; 
 struct macsec_tx_sa* macsec_txsa_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macsec_txsa_put (struct macsec_tx_sa*) ; 
 int /*<<< orphan*/  memmove (struct macsec_eth_header*,struct ethhdr*,int) ; 
 int send_sci (struct macsec_secy*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int skb_cow_data (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 struct macsec_eth_header* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 
 int skb_to_sgvec (struct sk_buff*,struct scatterlist*,int /*<<< orphan*/ ,size_t) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct pcpu_secy_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ tx_sa_update_pn (struct macsec_tx_sa*,struct macsec_secy*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *macsec_encrypt(struct sk_buff *skb,
				      struct net_device *dev)
{
	int ret;
	struct scatterlist *sg;
	struct sk_buff *trailer;
	unsigned char *iv;
	struct ethhdr *eth;
	struct macsec_eth_header *hh;
	size_t unprotected_len;
	struct aead_request *req;
	struct macsec_secy *secy;
	struct macsec_tx_sc *tx_sc;
	struct macsec_tx_sa *tx_sa;
	struct macsec_dev *macsec = macsec_priv(dev);
	bool sci_present;
	u32 pn;

	secy = &macsec->secy;
	tx_sc = &secy->tx_sc;

	/* 10.5.1 TX SA assignment */
	tx_sa = macsec_txsa_get(tx_sc->sa[tx_sc->encoding_sa]);
	if (!tx_sa) {
		secy->operational = false;
		kfree_skb(skb);
		return ERR_PTR(-EINVAL);
	}

	if (unlikely(skb_headroom(skb) < MACSEC_NEEDED_HEADROOM ||
		     skb_tailroom(skb) < MACSEC_NEEDED_TAILROOM)) {
		struct sk_buff *nskb = skb_copy_expand(skb,
						       MACSEC_NEEDED_HEADROOM,
						       MACSEC_NEEDED_TAILROOM,
						       GFP_ATOMIC);
		if (likely(nskb)) {
			consume_skb(skb);
			skb = nskb;
		} else {
			macsec_txsa_put(tx_sa);
			kfree_skb(skb);
			return ERR_PTR(-ENOMEM);
		}
	} else {
		skb = skb_unshare(skb, GFP_ATOMIC);
		if (!skb) {
			macsec_txsa_put(tx_sa);
			return ERR_PTR(-ENOMEM);
		}
	}

	unprotected_len = skb->len;
	eth = eth_hdr(skb);
	sci_present = send_sci(secy);
	hh = skb_push(skb, macsec_extra_len(sci_present));
	memmove(hh, eth, 2 * ETH_ALEN);

	pn = tx_sa_update_pn(tx_sa, secy);
	if (pn == 0) {
		macsec_txsa_put(tx_sa);
		kfree_skb(skb);
		return ERR_PTR(-ENOLINK);
	}
	macsec_fill_sectag(hh, secy, pn, sci_present);
	macsec_set_shortlen(hh, unprotected_len - 2 * ETH_ALEN);

	skb_put(skb, secy->icv_len);

	if (skb->len - ETH_HLEN > macsec_priv(dev)->real_dev->mtu) {
		struct pcpu_secy_stats *secy_stats = this_cpu_ptr(macsec->stats);

		u64_stats_update_begin(&secy_stats->syncp);
		secy_stats->stats.OutPktsTooLong++;
		u64_stats_update_end(&secy_stats->syncp);

		macsec_txsa_put(tx_sa);
		kfree_skb(skb);
		return ERR_PTR(-EINVAL);
	}

	ret = skb_cow_data(skb, 0, &trailer);
	if (unlikely(ret < 0)) {
		macsec_txsa_put(tx_sa);
		kfree_skb(skb);
		return ERR_PTR(ret);
	}

	req = macsec_alloc_req(tx_sa->key.tfm, &iv, &sg, ret);
	if (!req) {
		macsec_txsa_put(tx_sa);
		kfree_skb(skb);
		return ERR_PTR(-ENOMEM);
	}

	macsec_fill_iv(iv, secy->sci, pn);

	sg_init_table(sg, ret);
	ret = skb_to_sgvec(skb, sg, 0, skb->len);
	if (unlikely(ret < 0)) {
		aead_request_free(req);
		macsec_txsa_put(tx_sa);
		kfree_skb(skb);
		return ERR_PTR(ret);
	}

	if (tx_sc->encrypt) {
		int len = skb->len - macsec_hdr_len(sci_present) -
			  secy->icv_len;
		aead_request_set_crypt(req, sg, sg, len, iv);
		aead_request_set_ad(req, macsec_hdr_len(sci_present));
	} else {
		aead_request_set_crypt(req, sg, sg, 0, iv);
		aead_request_set_ad(req, skb->len - secy->icv_len);
	}

	macsec_skb_cb(skb)->req = req;
	macsec_skb_cb(skb)->tx_sa = tx_sa;
	aead_request_set_callback(req, 0, macsec_encrypt_done, skb);

	dev_hold(skb->dev);
	ret = crypto_aead_encrypt(req);
	if (ret == -EINPROGRESS) {
		return ERR_PTR(ret);
	} else if (ret != 0) {
		dev_put(skb->dev);
		kfree_skb(skb);
		aead_request_free(req);
		macsec_txsa_put(tx_sa);
		return ERR_PTR(-EINVAL);
	}

	dev_put(skb->dev);
	aead_request_free(req);
	macsec_txsa_put(tx_sa);

	return skb;
}