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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rio_mport {int dummy; } ;

/* Variables and functions */
#define  RIO_EFB_SER_EPF_M1_ID 138 
#define  RIO_EFB_SER_EPF_M2_ID 137 
#define  RIO_EFB_SER_EPF_SW_M1_ID 136 
#define  RIO_EFB_SER_EPF_SW_M2_ID 135 
#define  RIO_EFB_SER_EP_FREE_ID 134 
#define  RIO_EFB_SER_EP_ID 133 
#define  RIO_EFB_SER_EP_M1_ID 132 
#define  RIO_EFB_SER_EP_M2_ID 131 
#define  RIO_EFB_SER_EP_REC_ID 130 
#define  RIO_EFB_SER_EP_SW_M1_ID 129 
#define  RIO_EFB_SER_EP_SW_M2_ID 128 
 int RIO_GET_BLOCK_ID (int) ; 
 int /*<<< orphan*/  rio_local_read_config_32 (struct rio_mport*,int,int*) ; 
 int rio_mport_get_efb (struct rio_mport*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rio_mport_read_config_32 (struct rio_mport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

u32
rio_mport_get_physefb(struct rio_mport *port, int local,
		      u16 destid, u8 hopcount, u32 *rmap)
{
	u32 ext_ftr_ptr;
	u32 ftr_header;

	ext_ftr_ptr = rio_mport_get_efb(port, local, destid, hopcount, 0);

	while (ext_ftr_ptr)  {
		if (local)
			rio_local_read_config_32(port, ext_ftr_ptr,
						 &ftr_header);
		else
			rio_mport_read_config_32(port, destid, hopcount,
						 ext_ftr_ptr, &ftr_header);

		ftr_header = RIO_GET_BLOCK_ID(ftr_header);
		switch (ftr_header) {

		case RIO_EFB_SER_EP_ID:
		case RIO_EFB_SER_EP_REC_ID:
		case RIO_EFB_SER_EP_FREE_ID:
		case RIO_EFB_SER_EP_M1_ID:
		case RIO_EFB_SER_EP_SW_M1_ID:
		case RIO_EFB_SER_EPF_M1_ID:
		case RIO_EFB_SER_EPF_SW_M1_ID:
			*rmap = 1;
			return ext_ftr_ptr;

		case RIO_EFB_SER_EP_M2_ID:
		case RIO_EFB_SER_EP_SW_M2_ID:
		case RIO_EFB_SER_EPF_M2_ID:
		case RIO_EFB_SER_EPF_SW_M2_ID:
			*rmap = 2;
			return ext_ftr_ptr;

		default:
			break;
		}

		ext_ftr_ptr = rio_mport_get_efb(port, local, destid,
						hopcount, ext_ftr_ptr);
	}

	return ext_ftr_ptr;
}