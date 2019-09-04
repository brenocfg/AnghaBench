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
struct smb2_sync_hdr {scalar_t__ Status; int /*<<< orphan*/  MessageId; int /*<<< orphan*/  Command; int /*<<< orphan*/  SessionId; int /*<<< orphan*/  TreeId; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 scalar_t__ STATUS_NETWORK_SESSION_EXPIRED ; 
 scalar_t__ STATUS_USER_SESSION_DELETED ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_smb3_ses_expired (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
smb2_is_session_expired(char *buf)
{
	struct smb2_sync_hdr *shdr = (struct smb2_sync_hdr *)buf;

	if (shdr->Status != STATUS_NETWORK_SESSION_EXPIRED &&
	    shdr->Status != STATUS_USER_SESSION_DELETED)
		return false;

	trace_smb3_ses_expired(shdr->TreeId, shdr->SessionId,
			       le16_to_cpu(shdr->Command),
			       le64_to_cpu(shdr->MessageId));
	cifs_dbg(FYI, "Session expired or deleted\n");

	return true;
}