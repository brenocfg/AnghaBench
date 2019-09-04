#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int index; int length; int /*<<< orphan*/  payload; } ;
struct TYPE_6__ {TYPE_2__ cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  control_bits; int /*<<< orphan*/  message_type; } ;
struct tfd_frame {TYPE_3__ u; TYPE_1__ control_flags; } ;
struct clx2_queue {size_t first_empty; int /*<<< orphan*/  reg_w; int /*<<< orphan*/  n_bd; } ;
struct clx2_tx_queue {int /*<<< orphan*/ ** txb; struct tfd_frame* bd; struct clx2_queue q; } ;
struct ipw_priv {int /*<<< orphan*/  hcmd_seq; struct clx2_tx_queue txq_cmd; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
 int /*<<< orphan*/  TFD_NEED_IRQ_MASK ; 
 int /*<<< orphan*/  TX_HOST_COMMAND_TYPE ; 
 int /*<<< orphan*/  _ipw_read32 (struct ipw_priv*,int) ; 
 size_t ipw_queue_inc_wrap (size_t,int /*<<< orphan*/ ) ; 
 int ipw_tx_queue_space (struct clx2_queue*) ; 
 int /*<<< orphan*/  ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct tfd_frame*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipw_queue_tx_hcmd(struct ipw_priv *priv, int hcmd, void *buf,
			     int len, int sync)
{
	struct clx2_tx_queue *txq = &priv->txq_cmd;
	struct clx2_queue *q = &txq->q;
	struct tfd_frame *tfd;

	if (ipw_tx_queue_space(q) < (sync ? 1 : 2)) {
		IPW_ERROR("No space for Tx\n");
		return -EBUSY;
	}

	tfd = &txq->bd[q->first_empty];
	txq->txb[q->first_empty] = NULL;

	memset(tfd, 0, sizeof(*tfd));
	tfd->control_flags.message_type = TX_HOST_COMMAND_TYPE;
	tfd->control_flags.control_bits = TFD_NEED_IRQ_MASK;
	priv->hcmd_seq++;
	tfd->u.cmd.index = hcmd;
	tfd->u.cmd.length = len;
	memcpy(tfd->u.cmd.payload, buf, len);
	q->first_empty = ipw_queue_inc_wrap(q->first_empty, q->n_bd);
	ipw_write32(priv, q->reg_w, q->first_empty);
	_ipw_read32(priv, 0x90);

	return 0;
}