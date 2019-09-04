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
struct efx_nic {int vf_count; } ;

/* Variables and functions */
 int EFX_VI_BASE ; 
 unsigned int EFX_VI_SCALE_MAX ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MCDI_DECLARE_BUF (int /*<<< orphan*/ ,size_t) ; 
 unsigned int MCDI_DWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MC_CMD_SRIOV ; 
 size_t MC_CMD_SRIOV_IN_LEN ; 
 size_t MC_CMD_SRIOV_OUT_LEN ; 
 int /*<<< orphan*/  SRIOV_IN_ENABLE ; 
 int /*<<< orphan*/  SRIOV_IN_VF_COUNT ; 
 int /*<<< orphan*/  SRIOV_IN_VI_BASE ; 
 int /*<<< orphan*/  SRIOV_OUT_VF_TOTAL ; 
 int /*<<< orphan*/  SRIOV_OUT_VI_SCALE ; 
 int efx_mcdi_rpc_quiet (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,size_t*) ; 
 int /*<<< orphan*/  inbuf ; 
 int /*<<< orphan*/  outbuf ; 

__attribute__((used)) static int efx_siena_sriov_cmd(struct efx_nic *efx, bool enable,
			       unsigned *vi_scale_out, unsigned *vf_total_out)
{
	MCDI_DECLARE_BUF(inbuf, MC_CMD_SRIOV_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_SRIOV_OUT_LEN);
	unsigned vi_scale, vf_total;
	size_t outlen;
	int rc;

	MCDI_SET_DWORD(inbuf, SRIOV_IN_ENABLE, enable ? 1 : 0);
	MCDI_SET_DWORD(inbuf, SRIOV_IN_VI_BASE, EFX_VI_BASE);
	MCDI_SET_DWORD(inbuf, SRIOV_IN_VF_COUNT, efx->vf_count);

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_SRIOV, inbuf, MC_CMD_SRIOV_IN_LEN,
				outbuf, MC_CMD_SRIOV_OUT_LEN, &outlen);
	if (rc)
		return rc;
	if (outlen < MC_CMD_SRIOV_OUT_LEN)
		return -EIO;

	vf_total = MCDI_DWORD(outbuf, SRIOV_OUT_VF_TOTAL);
	vi_scale = MCDI_DWORD(outbuf, SRIOV_OUT_VI_SCALE);
	if (vi_scale > EFX_VI_SCALE_MAX)
		return -EOPNOTSUPP;

	if (vi_scale_out)
		*vi_scale_out = vi_scale;
	if (vf_total_out)
		*vf_total_out = vf_total;

	return 0;
}