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
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */

void cifs_dump_mids(struct TCP_Server_Info *server)
{
#ifdef CONFIG_CIFS_DEBUG2
	struct list_head *tmp;
	struct mid_q_entry *mid_entry;

	if (server == NULL)
		return;

	cifs_dbg(VFS, "Dump pending requests:\n");
	spin_lock(&GlobalMid_Lock);
	list_for_each(tmp, &server->pending_mid_q) {
		mid_entry = list_entry(tmp, struct mid_q_entry, qhead);
		cifs_dbg(VFS, "State: %d Cmd: %d Pid: %d Cbdata: %p Mid %llu\n",
			 mid_entry->mid_state,
			 le16_to_cpu(mid_entry->command),
			 mid_entry->pid,
			 mid_entry->callback_data,
			 mid_entry->mid);
#ifdef CONFIG_CIFS_STATS2
		cifs_dbg(VFS, "IsLarge: %d buf: %p time rcv: %ld now: %ld\n",
			 mid_entry->large_buf,
			 mid_entry->resp_buf,
			 mid_entry->when_received,
			 jiffies);
#endif /* STATS2 */
		cifs_dbg(VFS, "IsMult: %d IsEnd: %d\n",
			 mid_entry->multiRsp, mid_entry->multiEnd);
		if (mid_entry->resp_buf) {
			cifs_dump_detail(mid_entry->resp_buf, server);
			cifs_dump_mem("existing buf: ",
				mid_entry->resp_buf, 62);
		}
	}
	spin_unlock(&GlobalMid_Lock);
#endif /* CONFIG_CIFS_DEBUG2 */
}