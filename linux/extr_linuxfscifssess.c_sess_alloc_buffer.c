#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smb_hdr {int /*<<< orphan*/  smb_buf_length; } ;
struct sess_data {int /*<<< orphan*/  buf0_type; TYPE_1__* iov; struct cifs_ses* ses; } ;
struct cifs_ses {int dummy; } ;
struct TYPE_2__ {char* iov_base; scalar_t__ iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_NO_BUFFER ; 
 int /*<<< orphan*/  CIFS_SMALL_BUFFER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMB_COM_SESSION_SETUP_ANDX ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct smb_hdr*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int small_smb_init_no_tc (int /*<<< orphan*/ ,int,struct cifs_ses*,void**) ; 

__attribute__((used)) static int
sess_alloc_buffer(struct sess_data *sess_data, int wct)
{
	int rc;
	struct cifs_ses *ses = sess_data->ses;
	struct smb_hdr *smb_buf;

	rc = small_smb_init_no_tc(SMB_COM_SESSION_SETUP_ANDX, wct, ses,
				  (void **)&smb_buf);

	if (rc)
		return rc;

	sess_data->iov[0].iov_base = (char *)smb_buf;
	sess_data->iov[0].iov_len = be32_to_cpu(smb_buf->smb_buf_length) + 4;
	/*
	 * This variable will be used to clear the buffer
	 * allocated above in case of any error in the calling function.
	 */
	sess_data->buf0_type = CIFS_SMALL_BUFFER;

	/* 2000 big enough to fit max user, domain, NOS name etc. */
	sess_data->iov[2].iov_base = kmalloc(2000, GFP_KERNEL);
	if (!sess_data->iov[2].iov_base) {
		rc = -ENOMEM;
		goto out_free_smb_buf;
	}

	return 0;

out_free_smb_buf:
	kfree(smb_buf);
	sess_data->iov[0].iov_base = NULL;
	sess_data->iov[0].iov_len = 0;
	sess_data->buf0_type = CIFS_NO_BUFFER;
	return rc;
}