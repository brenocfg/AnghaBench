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
typedef  void* u32 ;
struct tlp_rp_regpair_t {scalar_t__ ctrl; void* reg1; void* reg0; } ;
struct altera_pcie {int dummy; } ;

/* Variables and functions */
 scalar_t__ RP_TX_EOP ; 
 scalar_t__ RP_TX_SOP ; 
 int /*<<< orphan*/  tlp_write_tx (struct altera_pcie*,struct tlp_rp_regpair_t*) ; 

__attribute__((used)) static void tlp_write_packet(struct altera_pcie *pcie, u32 *headers,
			     u32 data, bool align)
{
	struct tlp_rp_regpair_t tlp_rp_regdata;

	tlp_rp_regdata.reg0 = headers[0];
	tlp_rp_regdata.reg1 = headers[1];
	tlp_rp_regdata.ctrl = RP_TX_SOP;
	tlp_write_tx(pcie, &tlp_rp_regdata);

	if (align) {
		tlp_rp_regdata.reg0 = headers[2];
		tlp_rp_regdata.reg1 = 0;
		tlp_rp_regdata.ctrl = 0;
		tlp_write_tx(pcie, &tlp_rp_regdata);

		tlp_rp_regdata.reg0 = data;
		tlp_rp_regdata.reg1 = 0;
	} else {
		tlp_rp_regdata.reg0 = headers[2];
		tlp_rp_regdata.reg1 = data;
	}

	tlp_rp_regdata.ctrl = RP_TX_EOP;
	tlp_write_tx(pcie, &tlp_rp_regdata);
}