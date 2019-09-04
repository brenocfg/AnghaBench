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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct se_portal_group {int dummy; } ;

/* Variables and functions */
 int get_unaligned_be16 (char*) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 
 char tolower (char) ; 

__attribute__((used)) static char *iscsi_parse_pr_out_transport_id(
	struct se_portal_group *se_tpg,
	char *buf,
	u32 *out_tid_len,
	char **port_nexus_ptr)
{
	char *p;
	u32 tid_len, padding;
	int i;
	u16 add_len;
	u8 format_code = (buf[0] & 0xc0);
	/*
	 * Check for FORMAT CODE 00b or 01b from spc4r17, section 7.5.4.6:
	 *
	 *       TransportID for initiator ports using SCSI over iSCSI,
	 *       from Table 388 -- iSCSI TransportID formats.
	 *
	 *    00b     Initiator port is identified using the world wide unique
	 *            SCSI device name of the iSCSI initiator
	 *            device containing the initiator port (see table 389).
	 *    01b     Initiator port is identified using the world wide unique
	 *            initiator port identifier (see table 390).10b to 11b
	 *            Reserved
	 */
	if ((format_code != 0x00) && (format_code != 0x40)) {
		pr_err("Illegal format code: 0x%02x for iSCSI"
			" Initiator Transport ID\n", format_code);
		return NULL;
	}
	/*
	 * If the caller wants the TransportID Length, we set that value for the
	 * entire iSCSI Tarnsport ID now.
	 */
	if (out_tid_len) {
		/* The shift works thanks to integer promotion rules */
		add_len = get_unaligned_be16(&buf[2]);

		tid_len = strlen(&buf[4]);
		tid_len += 4; /* Add four bytes for iSCSI Transport ID header */
		tid_len += 1; /* Add one byte for NULL terminator */
		padding = ((-tid_len) & 3);
		if (padding != 0)
			tid_len += padding;

		if ((add_len + 4) != tid_len) {
			pr_debug("LIO-Target Extracted add_len: %hu "
				"does not match calculated tid_len: %u,"
				" using tid_len instead\n", add_len+4, tid_len);
			*out_tid_len = tid_len;
		} else
			*out_tid_len = (add_len + 4);
	}
	/*
	 * Check for ',i,0x' separator between iSCSI Name and iSCSI Initiator
	 * Session ID as defined in Table 390 - iSCSI initiator port TransportID
	 * format.
	 */
	if (format_code == 0x40) {
		p = strstr(&buf[4], ",i,0x");
		if (!p) {
			pr_err("Unable to locate \",i,0x\" separator"
				" for Initiator port identifier: %s\n",
				&buf[4]);
			return NULL;
		}
		*p = '\0'; /* Terminate iSCSI Name */
		p += 5; /* Skip over ",i,0x" separator */

		*port_nexus_ptr = p;
		/*
		 * Go ahead and do the lower case conversion of the received
		 * 12 ASCII characters representing the ISID in the TransportID
		 * for comparison against the running iSCSI session's ISID from
		 * iscsi_target.c:lio_sess_get_initiator_sid()
		 */
		for (i = 0; i < 12; i++) {
			if (isdigit(*p)) {
				p++;
				continue;
			}
			*p = tolower(*p);
			p++;
		}
	}

	return &buf[4];
}