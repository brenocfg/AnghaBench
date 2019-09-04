#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct cifs_ses {struct TCP_Server_Info* server; } ;
struct TCP_Server_Info {int srv_count; int sec_ntlmssp; int /*<<< orphan*/  server_GUID; } ;
struct TYPE_5__ {char* GUID; int /*<<< orphan*/  SecurityBlob; } ;
struct TYPE_6__ {TYPE_1__ extended_response; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_3__ NEGOTIATE_RSP ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FYI ; 
 scalar_t__ SMB1_CLIENT_GUID_SIZE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cifs_tcp_ses_lock ; 
 int decode_negTokenInit (int /*<<< orphan*/ ,scalar_t__,struct TCP_Server_Info*) ; 
 scalar_t__ get_bcc (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
decode_ext_sec_blob(struct cifs_ses *ses, NEGOTIATE_RSP *pSMBr)
{
	int	rc = 0;
	u16	count;
	char	*guid = pSMBr->u.extended_response.GUID;
	struct TCP_Server_Info *server = ses->server;

	count = get_bcc(&pSMBr->hdr);
	if (count < SMB1_CLIENT_GUID_SIZE)
		return -EIO;

	spin_lock(&cifs_tcp_ses_lock);
	if (server->srv_count > 1) {
		spin_unlock(&cifs_tcp_ses_lock);
		if (memcmp(server->server_GUID, guid, SMB1_CLIENT_GUID_SIZE) != 0) {
			cifs_dbg(FYI, "server UID changed\n");
			memcpy(server->server_GUID, guid, SMB1_CLIENT_GUID_SIZE);
		}
	} else {
		spin_unlock(&cifs_tcp_ses_lock);
		memcpy(server->server_GUID, guid, SMB1_CLIENT_GUID_SIZE);
	}

	if (count == SMB1_CLIENT_GUID_SIZE) {
		server->sec_ntlmssp = true;
	} else {
		count -= SMB1_CLIENT_GUID_SIZE;
		rc = decode_negTokenInit(
			pSMBr->u.extended_response.SecurityBlob, count, server);
		if (rc != 1)
			return -EINVAL;
	}

	return 0;
}