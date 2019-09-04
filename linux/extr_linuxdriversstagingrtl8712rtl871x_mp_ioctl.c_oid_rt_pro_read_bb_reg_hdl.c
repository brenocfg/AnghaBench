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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; scalar_t__ adapter_context; } ;
struct bb_reg_param {int /*<<< orphan*/  value; scalar_t__ offset; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int BB_REG_BASE_ADDR ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RNDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  r8712_bb_reg_read (struct _adapter*,int) ; 

uint oid_rt_pro_read_bb_reg_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *Adapter = (struct _adapter *)
				   (poid_par_priv->adapter_context);
	struct bb_reg_param *pbbreg;
	u16 offset;
	u32 value;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	if (poid_par_priv->information_buf_len < sizeof(struct bb_reg_param))
		return RNDIS_STATUS_INVALID_LENGTH;
	pbbreg = (struct bb_reg_param *)(poid_par_priv->information_buf);
	offset = (u16)(pbbreg->offset) & 0xFFF; /*0ffset :0x800~0xfff*/
	if (offset < BB_REG_BASE_ADDR)
		offset |= BB_REG_BASE_ADDR;
	value = r8712_bb_reg_read(Adapter, offset);
	pbbreg->value = value;
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	return RNDIS_STATUS_SUCCESS;
}