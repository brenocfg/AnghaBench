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
struct dpaa2_fd {int dummy; } ;
struct dpaa2_eth_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  frames; } ;
struct dpaa2_eth_fq {int /*<<< orphan*/  flowid; int /*<<< orphan*/  (* consume ) (struct dpaa2_eth_priv*,struct dpaa2_eth_channel*,struct dpaa2_fd const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;TYPE_1__ stats; } ;
struct dpaa2_eth_channel {int /*<<< orphan*/  napi; int /*<<< orphan*/  store; struct dpaa2_eth_priv* priv; } ;
struct dpaa2_dq {int dummy; } ;

/* Variables and functions */
 struct dpaa2_fd* dpaa2_dq_fd (struct dpaa2_dq*) ; 
 scalar_t__ dpaa2_dq_fqd_ctx (struct dpaa2_dq*) ; 
 struct dpaa2_dq* dpaa2_io_store_next (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (struct dpaa2_eth_priv*,struct dpaa2_eth_channel*,struct dpaa2_fd const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int consume_frames(struct dpaa2_eth_channel *ch)
{
	struct dpaa2_eth_priv *priv = ch->priv;
	struct dpaa2_eth_fq *fq;
	struct dpaa2_dq *dq;
	const struct dpaa2_fd *fd;
	int cleaned = 0;
	int is_last;

	do {
		dq = dpaa2_io_store_next(ch->store, &is_last);
		if (unlikely(!dq)) {
			/* If we're here, we *must* have placed a
			 * volatile dequeue comnmand, so keep reading through
			 * the store until we get some sort of valid response
			 * token (either a valid frame or an "empty dequeue")
			 */
			continue;
		}

		fd = dpaa2_dq_fd(dq);
		fq = (struct dpaa2_eth_fq *)(uintptr_t)dpaa2_dq_fqd_ctx(dq);
		fq->stats.frames++;

		fq->consume(priv, ch, fd, &ch->napi, fq->flowid);
		cleaned++;
	} while (!is_last);

	return cleaned;
}