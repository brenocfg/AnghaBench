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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct efx_rss_context {scalar_t__ context_id; } ;
struct efx_nic {struct efx_ef10_nic_data* nic_data; } ;
struct efx_filter_spec {int flags; scalar_t__ dmaq_id; } ;
struct efx_ef10_nic_data {scalar_t__ vport_id; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 scalar_t__ EFX_EF10_RSS_CONTEXT_INVALID ; 
 int EFX_FILTER_FLAG_RX_RSS ; 
 scalar_t__ EFX_FILTER_RX_DMAQ_ID_DROP ; 
 int /*<<< orphan*/  FILTER_OP_IN_HANDLE ; 
 int /*<<< orphan*/  FILTER_OP_IN_OP ; 
 int /*<<< orphan*/  FILTER_OP_IN_PORT_ID ; 
 int /*<<< orphan*/  FILTER_OP_IN_RX_CONTEXT ; 
 int /*<<< orphan*/  FILTER_OP_IN_RX_DEST ; 
 int /*<<< orphan*/  FILTER_OP_IN_RX_MODE ; 
 int /*<<< orphan*/  FILTER_OP_IN_RX_QUEUE ; 
 int /*<<< orphan*/  FILTER_OP_IN_TX_DEST ; 
 int /*<<< orphan*/  FILTER_OP_IN_TX_DOMAIN ; 
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MCDI_SET_QWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC_CMD_FILTER_OP_EXT_IN_LEN ; 
 scalar_t__ MC_CMD_FILTER_OP_IN_OP_REPLACE ; 
 scalar_t__ MC_CMD_FILTER_OP_IN_RX_DEST_DROP ; 
 scalar_t__ MC_CMD_FILTER_OP_IN_RX_DEST_HOST ; 
 scalar_t__ MC_CMD_FILTER_OP_IN_RX_MODE_RSS ; 
 scalar_t__ MC_CMD_FILTER_OP_IN_RX_MODE_SIMPLE ; 
 scalar_t__ MC_CMD_FILTER_OP_IN_TX_DEST_DEFAULT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  efx_ef10_filter_push_prep_set_match_fields (struct efx_nic*,struct efx_filter_spec const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_ef10_filter_push_prep(struct efx_nic *efx,
				      const struct efx_filter_spec *spec,
				      efx_dword_t *inbuf, u64 handle,
				      struct efx_rss_context *ctx,
				      bool replacing)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	u32 flags = spec->flags;

	memset(inbuf, 0, MC_CMD_FILTER_OP_EXT_IN_LEN);

	/* If RSS filter, caller better have given us an RSS context */
	if (flags & EFX_FILTER_FLAG_RX_RSS) {
		/* We don't have the ability to return an error, so we'll just
		 * log a warning and disable RSS for the filter.
		 */
		if (WARN_ON_ONCE(!ctx))
			flags &= ~EFX_FILTER_FLAG_RX_RSS;
		else if (WARN_ON_ONCE(ctx->context_id == EFX_EF10_RSS_CONTEXT_INVALID))
			flags &= ~EFX_FILTER_FLAG_RX_RSS;
	}

	if (replacing) {
		MCDI_SET_DWORD(inbuf, FILTER_OP_IN_OP,
			       MC_CMD_FILTER_OP_IN_OP_REPLACE);
		MCDI_SET_QWORD(inbuf, FILTER_OP_IN_HANDLE, handle);
	} else {
		efx_ef10_filter_push_prep_set_match_fields(efx, spec, inbuf);
	}

	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_PORT_ID, nic_data->vport_id);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_DEST,
		       spec->dmaq_id == EFX_FILTER_RX_DMAQ_ID_DROP ?
		       MC_CMD_FILTER_OP_IN_RX_DEST_DROP :
		       MC_CMD_FILTER_OP_IN_RX_DEST_HOST);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_TX_DOMAIN, 0);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_TX_DEST,
		       MC_CMD_FILTER_OP_IN_TX_DEST_DEFAULT);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_QUEUE,
		       spec->dmaq_id == EFX_FILTER_RX_DMAQ_ID_DROP ?
		       0 : spec->dmaq_id);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_MODE,
		       (flags & EFX_FILTER_FLAG_RX_RSS) ?
		       MC_CMD_FILTER_OP_IN_RX_MODE_RSS :
		       MC_CMD_FILTER_OP_IN_RX_MODE_SIMPLE);
	if (flags & EFX_FILTER_FLAG_RX_RSS)
		MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_CONTEXT, ctx->context_id);
}