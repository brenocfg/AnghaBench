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
 void* cifs_buf_get () ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  header_assemble (struct smb_hdr*,int,struct cifs_tcon*,int) ; 

__attribute__((used)) static int
__smb_init(int smb_command, int wct, struct cifs_tcon *tcon,
			void **request_buf, void **response_buf)
{
	*request_buf = cifs_buf_get();
	if (*request_buf == NULL) {
		/* BB should we add a retry in here if not a writepage? */
		return -ENOMEM;
	}
    /* Although the original thought was we needed the response buf for  */
    /* potential retries of smb operations it turns out we can determine */
    /* from the mid flags when the request buffer can be resent without  */
    /* having to use a second distinct buffer for the response */
	if (response_buf)
		*response_buf = *request_buf;

	header_assemble((struct smb_hdr *) *request_buf, smb_command, tcon,
			wct);

	if (tcon != NULL)
		cifs_stats_inc(&tcon->num_smbs_sent);

	return 0;
}