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
struct smb_hdr {int dummy; } ;
struct cifs_tcon {int /*<<< orphan*/  num_smbs_sent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int cifs_reconnect_tcon (struct cifs_tcon*,int) ; 
 void* cifs_small_buf_get () ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  header_assemble (struct smb_hdr*,int,struct cifs_tcon*,int) ; 

__attribute__((used)) static int
small_smb_init(int smb_command, int wct, struct cifs_tcon *tcon,
		void **request_buf)
{
	int rc;

	rc = cifs_reconnect_tcon(tcon, smb_command);
	if (rc)
		return rc;

	*request_buf = cifs_small_buf_get();
	if (*request_buf == NULL) {
		/* BB should we add a retry in here if not a writepage? */
		return -ENOMEM;
	}

	header_assemble((struct smb_hdr *) *request_buf, smb_command,
			tcon, wct);

	if (tcon != NULL)
		cifs_stats_inc(&tcon->num_smbs_sent);

	return 0;
}