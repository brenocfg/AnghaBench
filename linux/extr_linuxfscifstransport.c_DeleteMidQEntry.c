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
struct mid_q_entry {int /*<<< orphan*/  resp_buf; scalar_t__ large_buf; int /*<<< orphan*/  mid_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MID_FREE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_buf_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_mid_q_entry_release (struct mid_q_entry*) ; 
 int /*<<< orphan*/  cifs_small_buf_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  midCount ; 

void
DeleteMidQEntry(struct mid_q_entry *midEntry)
{
#ifdef CONFIG_CIFS_STATS2
	__le16 command = midEntry->server->vals->lock_cmd;
	unsigned long now;
#endif
	midEntry->mid_state = MID_FREE;
	atomic_dec(&midCount);
	if (midEntry->large_buf)
		cifs_buf_release(midEntry->resp_buf);
	else
		cifs_small_buf_release(midEntry->resp_buf);
#ifdef CONFIG_CIFS_STATS2
	now = jiffies;
	/* commands taking longer than one second are indications that
	   something is wrong, unless it is quite a slow link or server */
	if (time_after(now, midEntry->when_alloc + HZ) &&
	    (midEntry->command != command)) {
		/* smb2slowcmd[NUMBER_OF_SMB2_COMMANDS] counts by command */
		if ((le16_to_cpu(midEntry->command) < NUMBER_OF_SMB2_COMMANDS) &&
		    (le16_to_cpu(midEntry->command) >= 0))
			cifs_stats_inc(&midEntry->server->smb2slowcmd[le16_to_cpu(midEntry->command)]);

		trace_smb3_slow_rsp(le16_to_cpu(midEntry->command),
			       midEntry->mid, midEntry->pid,
			       midEntry->when_sent, midEntry->when_received);
		if (cifsFYI & CIFS_TIMER) {
			pr_debug(" CIFS slow rsp: cmd %d mid %llu",
			       midEntry->command, midEntry->mid);
			pr_info(" A: 0x%lx S: 0x%lx R: 0x%lx\n",
			       now - midEntry->when_alloc,
			       now - midEntry->when_sent,
			       now - midEntry->when_received);
		}
	}
#endif
	cifs_mid_q_entry_release(midEntry);
}