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
struct smb2_sync_hdr {scalar_t__ Status; int Command; } ;
struct smb2_sess_setup_rsp {int /*<<< orphan*/  SecurityBufferLength; int /*<<< orphan*/  SecurityBufferOffset; } ;
struct smb2_read_rsp {int DataOffset; int /*<<< orphan*/  DataLength; } ;
struct smb2_query_info_rsp {int /*<<< orphan*/  OutputBufferLength; int /*<<< orphan*/  OutputBufferOffset; } ;
struct smb2_query_directory_rsp {int /*<<< orphan*/  OutputBufferLength; int /*<<< orphan*/  OutputBufferOffset; } ;
struct smb2_negotiate_rsp {int /*<<< orphan*/  SecurityBufferLength; int /*<<< orphan*/  SecurityBufferOffset; } ;
struct smb2_ioctl_rsp {int /*<<< orphan*/  OutputCount; int /*<<< orphan*/  OutputOffset; } ;
struct smb2_err_rsp {scalar_t__ StructureSize; } ;
struct smb2_create_rsp {int /*<<< orphan*/  CreateContextsLength; int /*<<< orphan*/  CreateContextsOffset; } ;

/* Variables and functions */
#define  SMB2_CHANGE_NOTIFY 135 
#define  SMB2_CREATE 134 
 scalar_t__ SMB2_ERROR_STRUCTURE_SIZE2 ; 
#define  SMB2_IOCTL 133 
#define  SMB2_NEGOTIATE 132 
#define  SMB2_QUERY_DIRECTORY 131 
#define  SMB2_QUERY_INFO 130 
#define  SMB2_READ 129 
#define  SMB2_SESSION_SETUP 128 
 scalar_t__ STATUS_MORE_PROCESSING_REQUIRED ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

char *
smb2_get_data_area_len(int *off, int *len, struct smb2_sync_hdr *shdr)
{
	*off = 0;
	*len = 0;

	/* error responses do not have data area */
	if (shdr->Status && shdr->Status != STATUS_MORE_PROCESSING_REQUIRED &&
	    (((struct smb2_err_rsp *)shdr)->StructureSize) ==
						SMB2_ERROR_STRUCTURE_SIZE2)
		return NULL;

	/*
	 * Following commands have data areas so we have to get the location
	 * of the data buffer offset and data buffer length for the particular
	 * command.
	 */
	switch (shdr->Command) {
	case SMB2_NEGOTIATE:
		*off = le16_to_cpu(
		  ((struct smb2_negotiate_rsp *)shdr)->SecurityBufferOffset);
		*len = le16_to_cpu(
		  ((struct smb2_negotiate_rsp *)shdr)->SecurityBufferLength);
		break;
	case SMB2_SESSION_SETUP:
		*off = le16_to_cpu(
		  ((struct smb2_sess_setup_rsp *)shdr)->SecurityBufferOffset);
		*len = le16_to_cpu(
		  ((struct smb2_sess_setup_rsp *)shdr)->SecurityBufferLength);
		break;
	case SMB2_CREATE:
		*off = le32_to_cpu(
		    ((struct smb2_create_rsp *)shdr)->CreateContextsOffset);
		*len = le32_to_cpu(
		    ((struct smb2_create_rsp *)shdr)->CreateContextsLength);
		break;
	case SMB2_QUERY_INFO:
		*off = le16_to_cpu(
		    ((struct smb2_query_info_rsp *)shdr)->OutputBufferOffset);
		*len = le32_to_cpu(
		    ((struct smb2_query_info_rsp *)shdr)->OutputBufferLength);
		break;
	case SMB2_READ:
		/* TODO: is this a bug ? */
		*off = ((struct smb2_read_rsp *)shdr)->DataOffset;
		*len = le32_to_cpu(((struct smb2_read_rsp *)shdr)->DataLength);
		break;
	case SMB2_QUERY_DIRECTORY:
		*off = le16_to_cpu(
		  ((struct smb2_query_directory_rsp *)shdr)->OutputBufferOffset);
		*len = le32_to_cpu(
		  ((struct smb2_query_directory_rsp *)shdr)->OutputBufferLength);
		break;
	case SMB2_IOCTL:
		*off = le32_to_cpu(
		  ((struct smb2_ioctl_rsp *)shdr)->OutputOffset);
		*len = le32_to_cpu(
		  ((struct smb2_ioctl_rsp *)shdr)->OutputCount);
		break;
	case SMB2_CHANGE_NOTIFY:
	default:
		/* BB FIXME for unimplemented cases above */
		cifs_dbg(VFS, "no length check for command\n");
		break;
	}

	/*
	 * Invalid length or offset probably means data area is invalid, but
	 * we have little choice but to ignore the data area in this case.
	 */
	if (*off > 4096) {
		cifs_dbg(VFS, "offset %d too large, data area ignored\n", *off);
		*len = 0;
		*off = 0;
	} else if (*off < 0) {
		cifs_dbg(VFS, "negative offset %d to data invalid ignore data area\n",
			 *off);
		*off = 0;
		*len = 0;
	} else if (*len < 0) {
		cifs_dbg(VFS, "negative data length %d invalid, data area ignored\n",
			 *len);
		*len = 0;
	} else if (*len > 128 * 1024) {
		cifs_dbg(VFS, "data area larger than 128K: %d\n", *len);
		*len = 0;
	}

	/* return pointer to beginning of data area, ie offset from SMB start */
	if ((*off != 0) && (*len != 0))
		return (char *)shdr + *off;
	else
		return NULL;
}