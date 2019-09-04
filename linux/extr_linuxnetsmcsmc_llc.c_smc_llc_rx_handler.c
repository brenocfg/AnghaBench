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
struct TYPE_6__ {int type; } ;
struct TYPE_7__ {int length; TYPE_2__ common; } ;
struct TYPE_8__ {TYPE_3__ hdr; } ;
union smc_llc_msg {int /*<<< orphan*/  delete_rkey; int /*<<< orphan*/  confirm_rkey_cont; int /*<<< orphan*/  confirm_rkey; int /*<<< orphan*/  delete_link; int /*<<< orphan*/  add_link; int /*<<< orphan*/  confirm_link; int /*<<< orphan*/  test_link; TYPE_4__ raw; } ;
struct smc_link {scalar_t__ state; } ;
struct ib_wc {int byte_len; TYPE_1__* qp; } ;
struct TYPE_5__ {scalar_t__ qp_context; } ;

/* Variables and functions */
#define  SMC_LLC_ADD_LINK 134 
#define  SMC_LLC_CONFIRM_LINK 133 
#define  SMC_LLC_CONFIRM_RKEY 132 
#define  SMC_LLC_CONFIRM_RKEY_CONT 131 
#define  SMC_LLC_DELETE_LINK 130 
#define  SMC_LLC_DELETE_RKEY 129 
#define  SMC_LLC_TEST_LINK 128 
 scalar_t__ SMC_LNK_INACTIVE ; 
 int /*<<< orphan*/  smc_llc_rx_add_link (struct smc_link*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_llc_rx_confirm_link (struct smc_link*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_llc_rx_confirm_rkey (struct smc_link*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_llc_rx_confirm_rkey_cont (struct smc_link*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_llc_rx_delete_link (struct smc_link*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_llc_rx_delete_rkey (struct smc_link*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_llc_rx_test_link (struct smc_link*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smc_llc_rx_handler(struct ib_wc *wc, void *buf)
{
	struct smc_link *link = (struct smc_link *)wc->qp->qp_context;
	union smc_llc_msg *llc = buf;

	if (wc->byte_len < sizeof(*llc))
		return; /* short message */
	if (llc->raw.hdr.length != sizeof(*llc))
		return; /* invalid message */
	if (link->state == SMC_LNK_INACTIVE)
		return; /* link not active, drop msg */

	switch (llc->raw.hdr.common.type) {
	case SMC_LLC_TEST_LINK:
		smc_llc_rx_test_link(link, &llc->test_link);
		break;
	case SMC_LLC_CONFIRM_LINK:
		smc_llc_rx_confirm_link(link, &llc->confirm_link);
		break;
	case SMC_LLC_ADD_LINK:
		smc_llc_rx_add_link(link, &llc->add_link);
		break;
	case SMC_LLC_DELETE_LINK:
		smc_llc_rx_delete_link(link, &llc->delete_link);
		break;
	case SMC_LLC_CONFIRM_RKEY:
		smc_llc_rx_confirm_rkey(link, &llc->confirm_rkey);
		break;
	case SMC_LLC_CONFIRM_RKEY_CONT:
		smc_llc_rx_confirm_rkey_cont(link, &llc->confirm_rkey_cont);
		break;
	case SMC_LLC_DELETE_RKEY:
		smc_llc_rx_delete_rkey(link, &llc->delete_rkey);
		break;
	}
}