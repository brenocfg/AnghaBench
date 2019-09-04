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

/* Variables and functions */
 int GetCurrentThreadId () ; 
 int SEQ4_STATUS_ADMIN_STATE_REVOKED ; 
 int SEQ4_STATUS_BACKCHANNEL_FAULT ; 
 int SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIRED ; 
 int SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIRING ; 
 int SEQ4_STATUS_CB_PATH_DOWN ; 
 int SEQ4_STATUS_CB_PATH_DOWN_SESSION ; 
 int SEQ4_STATUS_DEVID_CHANGED ; 
 int SEQ4_STATUS_DEVID_DELETED ; 
 int SEQ4_STATUS_EXPIRED_ALL_STATE_REVOKED ; 
 int SEQ4_STATUS_EXPIRED_SOME_STATE_REVOKED ; 
 int SEQ4_STATUS_LEASE_MOVED ; 
 int SEQ4_STATUS_RECALLABLE_STATE_REVOKED ; 
 int SEQ4_STATUS_RESTART_RECLAIM_NEEDED ; 
 int /*<<< orphan*/  dlog_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int g_debug_level ; 

void print_sr_status_flags(int level, int flags)
{
    if (level > g_debug_level) return;
    fprintf(dlog_file, "%04x: sr_status_flags: ", GetCurrentThreadId());
    if (flags & SEQ4_STATUS_CB_PATH_DOWN) 
        fprintf(dlog_file, "SEQ4_STATUS_CB_PATH_DOWN ");
    if (flags & SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIRING) 
        fprintf(dlog_file, "SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIRING ");
    if (flags & SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIRED) 
        fprintf(dlog_file, "SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIRED ");
    if (flags & SEQ4_STATUS_EXPIRED_ALL_STATE_REVOKED) 
        fprintf(dlog_file, "SEQ4_STATUS_EXPIRED_ALL_STATE_REVOKED ");
    if (flags & SEQ4_STATUS_EXPIRED_SOME_STATE_REVOKED) 
        fprintf(dlog_file, "SEQ4_STATUS_EXPIRED_SOME_STATE_REVOKED ");
    if (flags & SEQ4_STATUS_ADMIN_STATE_REVOKED) 
        fprintf(dlog_file, "SEQ4_STATUS_ADMIN_STATE_REVOKED ");
    if (flags & SEQ4_STATUS_RECALLABLE_STATE_REVOKED) 
        fprintf(dlog_file, "SEQ4_STATUS_RECALLABLE_STATE_REVOKED ");
    if (flags & SEQ4_STATUS_LEASE_MOVED) 
        fprintf(dlog_file, "SEQ4_STATUS_LEASE_MOVED ");
    if (flags & SEQ4_STATUS_RESTART_RECLAIM_NEEDED) 
        fprintf(dlog_file, "SEQ4_STATUS_RESTART_RECLAIM_NEEDED ");
    if (flags & SEQ4_STATUS_CB_PATH_DOWN_SESSION) 
        fprintf(dlog_file, "SEQ4_STATUS_CB_PATH_DOWN_SESSION ");
    if (flags & SEQ4_STATUS_BACKCHANNEL_FAULT) 
        fprintf(dlog_file, "SEQ4_STATUS_BACKCHANNEL_FAULT ");
    if (flags & SEQ4_STATUS_DEVID_CHANGED) 
        fprintf(dlog_file, "SEQ4_STATUS_DEVID_CHANGED ");
    if (flags & SEQ4_STATUS_DEVID_DELETED) 
        fprintf(dlog_file, "SEQ4_STATUS_DEVID_DELETED ");
    fprintf(dlog_file, "\n");
}