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
struct smb_hdr {int /*<<< orphan*/  Flags2; int /*<<< orphan*/  Mid; } ;
struct cifs_ses {int capabilities; int /*<<< orphan*/  server; } ;

/* Variables and functions */
 int CAP_STATUS32 ; 
 int CAP_UNICODE ; 
 int /*<<< orphan*/  SMBFLG2_ERR_STATUS ; 
 int /*<<< orphan*/  SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  get_next_mid (int /*<<< orphan*/ ) ; 
 int small_smb_init (int const,int const,int /*<<< orphan*/ *,void**) ; 

int
small_smb_init_no_tc(const int smb_command, const int wct,
		     struct cifs_ses *ses, void **request_buf)
{
	int rc;
	struct smb_hdr *buffer;

	rc = small_smb_init(smb_command, wct, NULL, request_buf);
	if (rc)
		return rc;

	buffer = (struct smb_hdr *)*request_buf;
	buffer->Mid = get_next_mid(ses->server);
	if (ses->capabilities & CAP_UNICODE)
		buffer->Flags2 |= SMBFLG2_UNICODE;
	if (ses->capabilities & CAP_STATUS32)
		buffer->Flags2 |= SMBFLG2_ERR_STATUS;

	/* uid, tid can stay at zero as set in header assemble */

	/* BB add support for turning on the signing when
	this function is used after 1st of session setup requests */

	return rc;
}