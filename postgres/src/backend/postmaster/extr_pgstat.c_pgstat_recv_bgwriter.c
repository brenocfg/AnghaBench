#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buf_alloc; int /*<<< orphan*/  buf_fsync_backend; int /*<<< orphan*/  buf_written_backend; int /*<<< orphan*/  maxwritten_clean; int /*<<< orphan*/  buf_written_clean; int /*<<< orphan*/  buf_written_checkpoints; int /*<<< orphan*/  checkpoint_sync_time; int /*<<< orphan*/  checkpoint_write_time; int /*<<< orphan*/  requested_checkpoints; int /*<<< orphan*/  timed_checkpoints; } ;
struct TYPE_4__ {scalar_t__ m_buf_alloc; scalar_t__ m_buf_fsync_backend; scalar_t__ m_buf_written_backend; scalar_t__ m_maxwritten_clean; scalar_t__ m_buf_written_clean; scalar_t__ m_buf_written_checkpoints; scalar_t__ m_checkpoint_sync_time; scalar_t__ m_checkpoint_write_time; scalar_t__ m_requested_checkpoints; scalar_t__ m_timed_checkpoints; } ;
typedef  TYPE_1__ PgStat_MsgBgWriter ;

/* Variables and functions */
 TYPE_3__ globalStats ; 

__attribute__((used)) static void
pgstat_recv_bgwriter(PgStat_MsgBgWriter *msg, int len)
{
	globalStats.timed_checkpoints += msg->m_timed_checkpoints;
	globalStats.requested_checkpoints += msg->m_requested_checkpoints;
	globalStats.checkpoint_write_time += msg->m_checkpoint_write_time;
	globalStats.checkpoint_sync_time += msg->m_checkpoint_sync_time;
	globalStats.buf_written_checkpoints += msg->m_buf_written_checkpoints;
	globalStats.buf_written_clean += msg->m_buf_written_clean;
	globalStats.maxwritten_clean += msg->m_maxwritten_clean;
	globalStats.buf_written_backend += msg->m_buf_written_backend;
	globalStats.buf_fsync_backend += msg->m_buf_fsync_backend;
	globalStats.buf_alloc += msg->m_buf_alloc;
}