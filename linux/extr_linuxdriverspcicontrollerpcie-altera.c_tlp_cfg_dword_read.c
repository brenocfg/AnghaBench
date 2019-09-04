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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct altera_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLP_CFGRD_DW0 (struct altera_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLP_CFG_DW1 (struct altera_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLP_CFG_DW2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int TLP_HDR_SIZE ; 
 int /*<<< orphan*/  TLP_READ_TAG ; 
 int tlp_read_packet (struct altera_pcie*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlp_write_packet (struct altera_pcie*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tlp_cfg_dword_read(struct altera_pcie *pcie, u8 bus, u32 devfn,
			      int where, u8 byte_en, u32 *value)
{
	u32 headers[TLP_HDR_SIZE];

	headers[0] = TLP_CFGRD_DW0(pcie, bus);
	headers[1] = TLP_CFG_DW1(pcie, TLP_READ_TAG, byte_en);
	headers[2] = TLP_CFG_DW2(bus, devfn, where);

	tlp_write_packet(pcie, headers, 0, false);

	return tlp_read_packet(pcie, value);
}