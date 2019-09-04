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
typedef  int u8 ;
struct intel_ntb_dev {int dummy; } ;
typedef  enum ntb_topo { ____Placeholder_ntb_topo } ntb_topo ;

/* Variables and functions */
 int NTB_TOPO_B2B_DSD ; 
 int NTB_TOPO_B2B_USD ; 
 int NTB_TOPO_NONE ; 
 int NTB_TOPO_PRI ; 
 int NTB_TOPO_SEC ; 
#define  XEON_PPD_TOPO_B2B_DSD 133 
#define  XEON_PPD_TOPO_B2B_USD 132 
 int XEON_PPD_TOPO_MASK ; 
#define  XEON_PPD_TOPO_PRI_DSD 131 
#define  XEON_PPD_TOPO_PRI_USD 130 
#define  XEON_PPD_TOPO_SEC_DSD 129 
#define  XEON_PPD_TOPO_SEC_USD 128 

enum ntb_topo xeon_ppd_topo(struct intel_ntb_dev *ndev, u8 ppd)
{
	switch (ppd & XEON_PPD_TOPO_MASK) {
	case XEON_PPD_TOPO_B2B_USD:
		return NTB_TOPO_B2B_USD;

	case XEON_PPD_TOPO_B2B_DSD:
		return NTB_TOPO_B2B_DSD;

	case XEON_PPD_TOPO_PRI_USD:
	case XEON_PPD_TOPO_PRI_DSD: /* accept bogus PRI_DSD */
		return NTB_TOPO_PRI;

	case XEON_PPD_TOPO_SEC_USD:
	case XEON_PPD_TOPO_SEC_DSD: /* accept bogus SEC_DSD */
		return NTB_TOPO_SEC;
	}

	return NTB_TOPO_NONE;
}