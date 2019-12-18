#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct smb2_sync_hdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * smb2_com_sent; } ;
struct TYPE_4__ {TYPE_1__ smb2_stats; } ;
struct cifs_tcon {int /*<<< orphan*/  num_smbs_sent; TYPE_2__ stats; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ SMB2_SET_INFO ; 
 void* cifs_buf_get () ; 
 void* cifs_small_buf_get () ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_small_buf (scalar_t__,struct cifs_tcon*,struct smb2_sync_hdr*,unsigned int*) ; 
 size_t le16_to_cpu (scalar_t__) ; 
 int smb2_reconnect (scalar_t__,struct cifs_tcon*) ; 

__attribute__((used)) static int
smb2_plain_req_init(__le16 smb2_command, struct cifs_tcon *tcon,
		    void **request_buf, unsigned int *total_len)
{
	int rc;

	rc = smb2_reconnect(smb2_command, tcon);
	if (rc)
		return rc;

	/* BB eventually switch this to SMB2 specific small buf size */
	if (smb2_command == SMB2_SET_INFO)
		*request_buf = cifs_buf_get();
	else
		*request_buf = cifs_small_buf_get();
	if (*request_buf == NULL) {
		/* BB should we add a retry in here if not a writepage? */
		return -ENOMEM;
	}

	fill_small_buf(smb2_command, tcon,
		       (struct smb2_sync_hdr *)(*request_buf),
		       total_len);

	if (tcon != NULL) {
		uint16_t com_code = le16_to_cpu(smb2_command);
		cifs_stats_inc(&tcon->stats.smb2_stats.smb2_com_sent[com_code]);
		cifs_stats_inc(&tcon->num_smbs_sent);
	}

	return rc;
}