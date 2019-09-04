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
typedef  int u_int ;
struct sym_hcb {int dummy; } ;
struct TYPE_4__ {scalar_t__ lastp; } ;
struct TYPE_6__ {TYPE_2__* data; TYPE_1__ head; } ;
struct sym_ccb {int xerr_status; scalar_t__ goalp; scalar_t__ startp; int data_len; int odd_byte_adjustment; int host_flags; int ext_ofs; int ext_sg; TYPE_3__ phys; scalar_t__ extra_bytes; } ;
struct TYPE_5__ {scalar_t__ size; } ;

/* Variables and functions */
 int HF_SENSE ; 
 int SYM_CONF_MAX_SG ; 
 int XE_EXTRA_DATA ; 
 int XE_SODL_UNRUN ; 
 int XE_SWIDE_OVRUN ; 
 int scr_to_cpu (scalar_t__) ; 
 scalar_t__ sym_evaluate_dp (struct sym_hcb*,struct sym_ccb*,int,int*) ; 

int sym_compute_residual(struct sym_hcb *np, struct sym_ccb *cp)
{
	int dp_sg, resid = 0;
	int dp_ofs = 0;

	/*
	 *  Check for some data lost or just thrown away.
	 *  We are not required to be quite accurate in this 
	 *  situation. Btw, if we are odd for output and the 
	 *  device claims some more data, it may well happen 
	 *  than our residual be zero. :-)
	 */
	if (cp->xerr_status & (XE_EXTRA_DATA|XE_SODL_UNRUN|XE_SWIDE_OVRUN)) {
		if (cp->xerr_status & XE_EXTRA_DATA)
			resid -= cp->extra_bytes;
		if (cp->xerr_status & XE_SODL_UNRUN)
			++resid;
		if (cp->xerr_status & XE_SWIDE_OVRUN)
			--resid;
	}

	/*
	 *  If all data has been transferred,
	 *  there is no residual.
	 */
	if (cp->phys.head.lastp == cp->goalp)
		return resid;

	/*
	 *  If no data transfer occurs, or if the data
	 *  pointer is weird, return full residual.
	 */
	if (cp->startp == cp->phys.head.lastp ||
	    sym_evaluate_dp(np, cp, scr_to_cpu(cp->phys.head.lastp),
			    &dp_ofs) < 0) {
		return cp->data_len - cp->odd_byte_adjustment;
	}

	/*
	 *  If we were auto-sensing, then we are done.
	 */
	if (cp->host_flags & HF_SENSE) {
		return -dp_ofs;
	}

	/*
	 *  We are now full comfortable in the computation 
	 *  of the data residual (2's complement).
	 */
	resid = -cp->ext_ofs;
	for (dp_sg = cp->ext_sg; dp_sg < SYM_CONF_MAX_SG; ++dp_sg) {
		u_int tmp = scr_to_cpu(cp->phys.data[dp_sg].size);
		resid += (tmp & 0xffffff);
	}

	resid -= cp->odd_byte_adjustment;

	/*
	 *  Hopefully, the result is not too wrong.
	 */
	return resid;
}