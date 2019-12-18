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
struct seq_file {int dummy; } ;
struct cifs_tcon {int capabilities; int ss_flags; scalar_t__ maximal_access; scalar_t__ perf_sector_size; scalar_t__ tid; scalar_t__ share_flags; } ;

/* Variables and functions */
 int SMB2_SHARE_CAP_ASYMMETRIC ; 
 int SMB2_SHARE_CAP_CLUSTER ; 
 int SMB2_SHARE_CAP_CONTINUOUS_AVAILABILITY ; 
 int SMB2_SHARE_CAP_DFS ; 
 int SMB2_SHARE_CAP_SCALEOUT ; 
 int SSINFO_FLAGS_ALIGNED_DEVICE ; 
 int SSINFO_FLAGS_NO_SEEK_PENALTY ; 
 int SSINFO_FLAGS_PARTITION_ALIGNED_ON_DEVICE ; 
 int SSINFO_FLAGS_TRIM_ENABLED ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void
smb2_dump_share_caps(struct seq_file *m, struct cifs_tcon *tcon)
{
	seq_puts(m, "\n\tShare Capabilities:");
	if (tcon->capabilities & SMB2_SHARE_CAP_DFS)
		seq_puts(m, " DFS,");
	if (tcon->capabilities & SMB2_SHARE_CAP_CONTINUOUS_AVAILABILITY)
		seq_puts(m, " CONTINUOUS AVAILABILITY,");
	if (tcon->capabilities & SMB2_SHARE_CAP_SCALEOUT)
		seq_puts(m, " SCALEOUT,");
	if (tcon->capabilities & SMB2_SHARE_CAP_CLUSTER)
		seq_puts(m, " CLUSTER,");
	if (tcon->capabilities & SMB2_SHARE_CAP_ASYMMETRIC)
		seq_puts(m, " ASYMMETRIC,");
	if (tcon->capabilities == 0)
		seq_puts(m, " None");
	if (tcon->ss_flags & SSINFO_FLAGS_ALIGNED_DEVICE)
		seq_puts(m, " Aligned,");
	if (tcon->ss_flags & SSINFO_FLAGS_PARTITION_ALIGNED_ON_DEVICE)
		seq_puts(m, " Partition Aligned,");
	if (tcon->ss_flags & SSINFO_FLAGS_NO_SEEK_PENALTY)
		seq_puts(m, " SSD,");
	if (tcon->ss_flags & SSINFO_FLAGS_TRIM_ENABLED)
		seq_puts(m, " TRIM-support,");

	seq_printf(m, "\tShare Flags: 0x%x", tcon->share_flags);
	seq_printf(m, "\n\ttid: 0x%x", tcon->tid);
	if (tcon->perf_sector_size)
		seq_printf(m, "\tOptimal sector size: 0x%x",
			   tcon->perf_sector_size);
	seq_printf(m, "\tMaximal Access: 0x%x", tcon->maximal_access);
}