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
struct rocker {struct ofdpa* wpriv; } ;
struct ofdpa_port {int dummy; } ;
struct ofdpa {scalar_t__ fib_aborted; } ;
struct fib_entry_notifier_info {int /*<<< orphan*/  tb_id; TYPE_2__* fi; int /*<<< orphan*/  dst_len; int /*<<< orphan*/  dst; } ;
struct TYPE_4__ {TYPE_1__* fib_nh; int /*<<< orphan*/  fib_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  nh_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFDPA_OP_FLAG_REMOVE ; 
 int /*<<< orphan*/  RTNH_F_OFFLOAD ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct ofdpa_port* ofdpa_port_dev_lower_find (int /*<<< orphan*/ ,struct rocker*) ; 
 int ofdpa_port_fib_ipv4 (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_fib4_del(struct rocker *rocker,
			  const struct fib_entry_notifier_info *fen_info)
{
	struct ofdpa *ofdpa = rocker->wpriv;
	struct ofdpa_port *ofdpa_port;

	if (ofdpa->fib_aborted)
		return 0;
	ofdpa_port = ofdpa_port_dev_lower_find(fen_info->fi->fib_dev, rocker);
	if (!ofdpa_port)
		return 0;
	fen_info->fi->fib_nh->nh_flags &= ~RTNH_F_OFFLOAD;
	return ofdpa_port_fib_ipv4(ofdpa_port, htonl(fen_info->dst),
				   fen_info->dst_len, fen_info->fi,
				   fen_info->tb_id, OFDPA_OP_FLAG_REMOVE);
}