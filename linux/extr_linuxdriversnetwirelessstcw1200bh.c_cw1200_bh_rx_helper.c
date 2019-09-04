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
typedef  int uint16_t ;
typedef  int u8 ;
typedef  int u16 ;
struct wsm_hdr {int /*<<< orphan*/  id; int /*<<< orphan*/  len; } ;
struct sk_buff {int* data; } ;
struct cw1200_common {int wsm_rx_seq; scalar_t__ wsm_enable_wsm_dumps; int /*<<< orphan*/  hwbus_priv; TYPE_1__* hwbus_ops; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {size_t (* align_size ) (int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 size_t EFFECTIVE_BUF_SIZE ; 
 int ST90TDS_CONT_NEXT_LEN_MASK ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int cw1200_data_read (struct cw1200_common*,int*,size_t) ; 
 struct sk_buff* dev_alloc_skb (size_t) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,...) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,size_t) ; 
 size_t stub1 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wsm_handle_exception (struct cw1200_common*,int*,size_t) ; 
 int wsm_handle_rx (struct cw1200_common*,int,struct wsm_hdr*,struct sk_buff**) ; 
 int wsm_release_tx_buffer (struct cw1200_common*,int) ; 

__attribute__((used)) static int cw1200_bh_rx_helper(struct cw1200_common *priv,
			       uint16_t *ctrl_reg,
			       int *tx)
{
	size_t read_len = 0;
	struct sk_buff *skb_rx = NULL;
	struct wsm_hdr *wsm;
	size_t wsm_len;
	u16 wsm_id;
	u8 wsm_seq;
	int rx_resync = 1;

	size_t alloc_len;
	u8 *data;

	read_len = (*ctrl_reg & ST90TDS_CONT_NEXT_LEN_MASK) * 2;
	if (!read_len)
		return 0; /* No more work */

	if (WARN_ON((read_len < sizeof(struct wsm_hdr)) ||
		    (read_len > EFFECTIVE_BUF_SIZE))) {
		pr_debug("Invalid read len: %zu (%04x)",
			 read_len, *ctrl_reg);
		goto err;
	}

	/* Add SIZE of PIGGYBACK reg (CONTROL Reg)
	 * to the NEXT Message length + 2 Bytes for SKB
	 */
	read_len = read_len + 2;

	alloc_len = priv->hwbus_ops->align_size(
		priv->hwbus_priv, read_len);

	/* Check if not exceeding CW1200 capabilities */
	if (WARN_ON_ONCE(alloc_len > EFFECTIVE_BUF_SIZE)) {
		pr_debug("Read aligned len: %zu\n",
			 alloc_len);
	}

	skb_rx = dev_alloc_skb(alloc_len);
	if (WARN_ON(!skb_rx))
		goto err;

	skb_trim(skb_rx, 0);
	skb_put(skb_rx, read_len);
	data = skb_rx->data;
	if (WARN_ON(!data))
		goto err;

	if (WARN_ON(cw1200_data_read(priv, data, alloc_len))) {
		pr_err("rx blew up, len %zu\n", alloc_len);
		goto err;
	}

	/* Piggyback */
	*ctrl_reg = __le16_to_cpu(
		((__le16 *)data)[alloc_len / 2 - 1]);

	wsm = (struct wsm_hdr *)data;
	wsm_len = __le16_to_cpu(wsm->len);
	if (WARN_ON(wsm_len > read_len))
		goto err;

	if (priv->wsm_enable_wsm_dumps)
		print_hex_dump_bytes("<-- ",
				     DUMP_PREFIX_NONE,
				     data, wsm_len);

	wsm_id  = __le16_to_cpu(wsm->id) & 0xFFF;
	wsm_seq = (__le16_to_cpu(wsm->id) >> 13) & 7;

	skb_trim(skb_rx, wsm_len);

	if (wsm_id == 0x0800) {
		wsm_handle_exception(priv,
				     &data[sizeof(*wsm)],
				     wsm_len - sizeof(*wsm));
		goto err;
	} else if (!rx_resync) {
		if (WARN_ON(wsm_seq != priv->wsm_rx_seq))
			goto err;
	}
	priv->wsm_rx_seq = (wsm_seq + 1) & 7;
	rx_resync = 0;

	if (wsm_id & 0x0400) {
		int rc = wsm_release_tx_buffer(priv, 1);
		if (WARN_ON(rc < 0))
			return rc;
		else if (rc > 0)
			*tx = 1;
	}

	/* cw1200_wsm_rx takes care on SKB livetime */
	if (WARN_ON(wsm_handle_rx(priv, wsm_id, wsm, &skb_rx)))
		goto err;

	if (skb_rx) {
		dev_kfree_skb(skb_rx);
		skb_rx = NULL;
	}

	return 0;

err:
	if (skb_rx) {
		dev_kfree_skb(skb_rx);
		skb_rx = NULL;
	}
	return -1;
}