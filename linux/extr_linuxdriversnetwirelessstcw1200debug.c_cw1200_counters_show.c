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
struct wsm_mib_counters_table {int /*<<< orphan*/  rx_mgmt_ccmp_replays; int /*<<< orphan*/  rx_cmac_replays; int /*<<< orphan*/  rx_cmac_icv_errors; int /*<<< orphan*/  rx_frames_success; int /*<<< orphan*/  rx_multicast_frames; int /*<<< orphan*/  ack_failures; int /*<<< orphan*/  rts_failures; int /*<<< orphan*/  rts_success; int /*<<< orphan*/  rx_frame_duplicates; int /*<<< orphan*/  tx_frames_multi_retried; int /*<<< orphan*/  tx_frames_retried; int /*<<< orphan*/  tx_frame_failures; int /*<<< orphan*/  tx_frames_success; int /*<<< orphan*/  tx_multicast_frames; int /*<<< orphan*/  rx_no_key_failures; int /*<<< orphan*/  rx_mic_failures; int /*<<< orphan*/  rx_decryption_failures; int /*<<< orphan*/  rx_packet_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  fcs_errors; int /*<<< orphan*/  plcp_errors; } ;
struct seq_file {struct cw1200_common* private; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ) ; 
 int wsm_get_counters_table (struct cw1200_common*,struct wsm_mib_counters_table*) ; 

__attribute__((used)) static int cw1200_counters_show(struct seq_file *seq, void *v)
{
	int ret;
	struct cw1200_common *priv = seq->private;
	struct wsm_mib_counters_table counters;

	ret = wsm_get_counters_table(priv, &counters);
	if (ret)
		return ret;

#define PUT_COUNTER(tab, name) \
	seq_printf(seq, "%s:" tab "%d\n", #name, \
		__le32_to_cpu(counters.name))

	PUT_COUNTER("\t\t", plcp_errors);
	PUT_COUNTER("\t\t", fcs_errors);
	PUT_COUNTER("\t\t", tx_packets);
	PUT_COUNTER("\t\t", rx_packets);
	PUT_COUNTER("\t\t", rx_packet_errors);
	PUT_COUNTER("\t",   rx_decryption_failures);
	PUT_COUNTER("\t\t", rx_mic_failures);
	PUT_COUNTER("\t",   rx_no_key_failures);
	PUT_COUNTER("\t",   tx_multicast_frames);
	PUT_COUNTER("\t",   tx_frames_success);
	PUT_COUNTER("\t",   tx_frame_failures);
	PUT_COUNTER("\t",   tx_frames_retried);
	PUT_COUNTER("\t",   tx_frames_multi_retried);
	PUT_COUNTER("\t",   rx_frame_duplicates);
	PUT_COUNTER("\t\t", rts_success);
	PUT_COUNTER("\t\t", rts_failures);
	PUT_COUNTER("\t\t", ack_failures);
	PUT_COUNTER("\t",   rx_multicast_frames);
	PUT_COUNTER("\t",   rx_frames_success);
	PUT_COUNTER("\t",   rx_cmac_icv_errors);
	PUT_COUNTER("\t\t", rx_cmac_replays);
	PUT_COUNTER("\t",   rx_mgmt_ccmp_replays);

#undef PUT_COUNTER

	return 0;
}