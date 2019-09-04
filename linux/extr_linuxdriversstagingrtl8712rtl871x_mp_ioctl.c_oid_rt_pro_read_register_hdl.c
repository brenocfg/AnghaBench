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
typedef  int /*<<< orphan*/  uint ;
typedef  int u16 ;
struct oid_par_priv {scalar_t__ type_of_oid; int /*<<< orphan*/  information_buf_len; int /*<<< orphan*/ * bytes_rw; scalar_t__ information_buf; scalar_t__ adapter_context; } ;
struct mp_rw_reg {int offset; int width; int /*<<< orphan*/  value; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  r8712_bb_reg_read (struct _adapter*,int) ; 
 int /*<<< orphan*/  r8712_read16 (struct _adapter*,int) ; 
 int /*<<< orphan*/  r8712_read32 (struct _adapter*,int) ; 
 int /*<<< orphan*/  r8712_read8 (struct _adapter*,int) ; 

uint oid_rt_pro_read_register_hdl(struct oid_par_priv
					 *poid_par_priv)
{
	struct _adapter *Adapter = (struct _adapter *)
				   (poid_par_priv->adapter_context);
	uint status = RNDIS_STATUS_SUCCESS;
	struct mp_rw_reg *RegRWStruct;
	u16		offset;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	RegRWStruct = (struct mp_rw_reg *)poid_par_priv->information_buf;
	if ((RegRWStruct->offset >= 0x10250800) &&
	    (RegRWStruct->offset <= 0x10250FFF)) {
		/*baseband register*/
		/*0ffset :0x800~0xfff*/
		offset = (u16)(RegRWStruct->offset) & 0xFFF;
		RegRWStruct->value = r8712_bb_reg_read(Adapter, offset);
	} else {
		switch (RegRWStruct->width) {
		case 1:
			RegRWStruct->value = r8712_read8(Adapter,
						   RegRWStruct->offset);
			break;
		case 2:
			RegRWStruct->value = r8712_read16(Adapter,
						    RegRWStruct->offset);
			break;
		case 4:
			RegRWStruct->value = r8712_read32(Adapter,
						    RegRWStruct->offset);
			break;
		default:
			status = RNDIS_STATUS_NOT_ACCEPTED;
			break;
		}
	}
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	return status;
}