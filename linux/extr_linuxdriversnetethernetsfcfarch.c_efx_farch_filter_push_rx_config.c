#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {int rx_scatter; struct efx_farch_filter_state* filter_state; } ;
struct efx_farch_filter_table {int* search_limit; TYPE_1__* spec; scalar_t__ size; } ;
struct efx_farch_filter_state {struct efx_farch_filter_table* table; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;
struct TYPE_2__ {int dmaq_id; int flags; } ;

/* Variables and functions */
 int EFX_FARCH_FILTER_CTL_SRCH_FUDGE_FULL ; 
 int EFX_FARCH_FILTER_CTL_SRCH_FUDGE_WILD ; 
 size_t EFX_FARCH_FILTER_INDEX_MC_DEF ; 
 size_t EFX_FARCH_FILTER_INDEX_UC_DEF ; 
 size_t EFX_FARCH_FILTER_MAC_FULL ; 
 size_t EFX_FARCH_FILTER_MAC_WILD ; 
 size_t EFX_FARCH_FILTER_TABLE_RX_DEF ; 
 size_t EFX_FARCH_FILTER_TABLE_RX_IP ; 
 size_t EFX_FARCH_FILTER_TABLE_RX_MAC ; 
 size_t EFX_FARCH_FILTER_TCP_FULL ; 
 size_t EFX_FARCH_FILTER_TCP_WILD ; 
 size_t EFX_FARCH_FILTER_UDP_FULL ; 
 size_t EFX_FARCH_FILTER_UDP_WILD ; 
 int EFX_FILTER_FLAG_RX_RSS ; 
 int EFX_FILTER_FLAG_RX_SCATTER ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_BZ_SCATTER_ENBL_NO_MATCH_Q ; 
 int /*<<< orphan*/  FRF_BZ_TCP_FULL_SRCH_LIMIT ; 
 int /*<<< orphan*/  FRF_BZ_TCP_WILD_SRCH_LIMIT ; 
 int /*<<< orphan*/  FRF_BZ_UDP_FULL_SRCH_LIMIT ; 
 int /*<<< orphan*/  FRF_BZ_UDP_WILD_SRCH_LIMIT ; 
 int /*<<< orphan*/  FRF_CZ_ETHERNET_FULL_SEARCH_LIMIT ; 
 int /*<<< orphan*/  FRF_CZ_ETHERNET_WILDCARD_SEARCH_LIMIT ; 
 int /*<<< orphan*/  FRF_CZ_MULTICAST_NOMATCH_Q_ID ; 
 int /*<<< orphan*/  FRF_CZ_MULTICAST_NOMATCH_RSS_ENABLED ; 
 int /*<<< orphan*/  FRF_CZ_UNICAST_NOMATCH_Q_ID ; 
 int /*<<< orphan*/  FRF_CZ_UNICAST_NOMATCH_RSS_ENABLED ; 
 int /*<<< orphan*/  FR_BZ_RX_FILTER_CTL ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_farch_filter_push_rx_config(struct efx_nic *efx)
{
	struct efx_farch_filter_state *state = efx->filter_state;
	struct efx_farch_filter_table *table;
	efx_oword_t filter_ctl;

	efx_reado(efx, &filter_ctl, FR_BZ_RX_FILTER_CTL);

	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_IP];
	EFX_SET_OWORD_FIELD(filter_ctl, FRF_BZ_TCP_FULL_SRCH_LIMIT,
			    table->search_limit[EFX_FARCH_FILTER_TCP_FULL] +
			    EFX_FARCH_FILTER_CTL_SRCH_FUDGE_FULL);
	EFX_SET_OWORD_FIELD(filter_ctl, FRF_BZ_TCP_WILD_SRCH_LIMIT,
			    table->search_limit[EFX_FARCH_FILTER_TCP_WILD] +
			    EFX_FARCH_FILTER_CTL_SRCH_FUDGE_WILD);
	EFX_SET_OWORD_FIELD(filter_ctl, FRF_BZ_UDP_FULL_SRCH_LIMIT,
			    table->search_limit[EFX_FARCH_FILTER_UDP_FULL] +
			    EFX_FARCH_FILTER_CTL_SRCH_FUDGE_FULL);
	EFX_SET_OWORD_FIELD(filter_ctl, FRF_BZ_UDP_WILD_SRCH_LIMIT,
			    table->search_limit[EFX_FARCH_FILTER_UDP_WILD] +
			    EFX_FARCH_FILTER_CTL_SRCH_FUDGE_WILD);

	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_MAC];
	if (table->size) {
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_ETHERNET_FULL_SEARCH_LIMIT,
			table->search_limit[EFX_FARCH_FILTER_MAC_FULL] +
			EFX_FARCH_FILTER_CTL_SRCH_FUDGE_FULL);
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_ETHERNET_WILDCARD_SEARCH_LIMIT,
			table->search_limit[EFX_FARCH_FILTER_MAC_WILD] +
			EFX_FARCH_FILTER_CTL_SRCH_FUDGE_WILD);
	}

	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_DEF];
	if (table->size) {
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_UNICAST_NOMATCH_Q_ID,
			table->spec[EFX_FARCH_FILTER_INDEX_UC_DEF].dmaq_id);
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_UNICAST_NOMATCH_RSS_ENABLED,
			!!(table->spec[EFX_FARCH_FILTER_INDEX_UC_DEF].flags &
			   EFX_FILTER_FLAG_RX_RSS));
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_MULTICAST_NOMATCH_Q_ID,
			table->spec[EFX_FARCH_FILTER_INDEX_MC_DEF].dmaq_id);
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_MULTICAST_NOMATCH_RSS_ENABLED,
			!!(table->spec[EFX_FARCH_FILTER_INDEX_MC_DEF].flags &
			   EFX_FILTER_FLAG_RX_RSS));

		/* There is a single bit to enable RX scatter for all
		 * unmatched packets.  Only set it if scatter is
		 * enabled in both filter specs.
		 */
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_BZ_SCATTER_ENBL_NO_MATCH_Q,
			!!(table->spec[EFX_FARCH_FILTER_INDEX_UC_DEF].flags &
			   table->spec[EFX_FARCH_FILTER_INDEX_MC_DEF].flags &
			   EFX_FILTER_FLAG_RX_SCATTER));
	} else {
		/* We don't expose 'default' filters because unmatched
		 * packets always go to the queue number found in the
		 * RSS table.  But we still need to set the RX scatter
		 * bit here.
		 */
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_BZ_SCATTER_ENBL_NO_MATCH_Q,
			efx->rx_scatter);
	}

	efx_writeo(efx, &filter_ctl, FR_BZ_RX_FILTER_CTL);
}