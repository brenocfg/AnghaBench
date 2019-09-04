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
typedef  int uint8 ;
typedef  scalar_t__ uint32 ;
typedef  int uint16 ;
struct stream {int* p; int* data; int size; int* end; int* rdp_hdr; } ;
struct TYPE_2__ {scalar_t__ hist; struct stream ns; } ;
typedef  struct stream* STREAM ;
typedef  int /*<<< orphan*/  RD_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  False ; 
#define  RDP_DATA_PDU_AUTORECONNECT_STATUS 135 
#define  RDP_DATA_PDU_BELL 134 
#define  RDP_DATA_PDU_CONTROL 133 
#define  RDP_DATA_PDU_DISCONNECT 132 
#define  RDP_DATA_PDU_LOGON 131 
#define  RDP_DATA_PDU_POINTER 130 
#define  RDP_DATA_PDU_SYNCHRONISE 129 
#define  RDP_DATA_PDU_UPDATE 128 
 int RDP_MPPC_COMPRESSED ; 
 scalar_t__ RDP_MPPC_DICT_SIZE ; 
 int /*<<< orphan*/  error (char*) ; 
 TYPE_1__ g_mppc_dict ; 
 int /*<<< orphan*/  in_uint16_le (struct stream*,int) ; 
 int /*<<< orphan*/  in_uint8 (struct stream*,int) ; 
 int /*<<< orphan*/  in_uint8s (struct stream*,int) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,scalar_t__) ; 
 int mppc_expand (int*,int,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  process_disconnect_pdu (struct stream*,scalar_t__*) ; 
 int /*<<< orphan*/  process_pdu_logon (struct stream*) ; 
 int /*<<< orphan*/  process_pointer_pdu (struct stream*) ; 
 int /*<<< orphan*/  process_update_pdu (struct stream*) ; 
 int /*<<< orphan*/  ui_bell () ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 
 int /*<<< orphan*/  warning (char*) ; 
 scalar_t__ xrealloc (int*,scalar_t__) ; 

__attribute__((used)) static RD_BOOL
process_data_pdu(STREAM s, uint32 * ext_disc_reason)
{
	uint8 data_pdu_type;
	uint8 ctype;
	uint16 clen;
	uint32 len;

	uint32 roff, rlen;

	struct stream *ns = &(g_mppc_dict.ns);

	in_uint8s(s, 6);	/* shareid, pad, streamid */
	in_uint16_le(s, len);
	in_uint8(s, data_pdu_type);
	in_uint8(s, ctype);
	in_uint16_le(s, clen);
	clen -= 18;

	if (ctype & RDP_MPPC_COMPRESSED)
	{
		if (len > RDP_MPPC_DICT_SIZE)
			error("error decompressed packet size exceeds max\n");
		if (mppc_expand(s->p, clen, ctype, &roff, &rlen) == -1)
			error("error while decompressing packet\n");

		/* len -= 18; */

		/* allocate memory and copy the uncompressed data into the temporary stream */
		ns->data = (uint8 *) xrealloc(ns->data, rlen);

		memcpy((ns->data), (unsigned char *) (g_mppc_dict.hist + roff), rlen);

		ns->size = rlen;
		ns->end = (ns->data + ns->size);
		ns->p = ns->data;
		ns->rdp_hdr = ns->p;

		s = ns;
	}

	switch (data_pdu_type)
	{
		case RDP_DATA_PDU_UPDATE:
			process_update_pdu(s);
			break;

		case RDP_DATA_PDU_CONTROL:
			DEBUG(("Received Control PDU\n"));
			break;

		case RDP_DATA_PDU_SYNCHRONISE:
			DEBUG(("Received Sync PDU\n"));
			break;

		case RDP_DATA_PDU_POINTER:
			process_pointer_pdu(s);
			break;

		case RDP_DATA_PDU_BELL:
			ui_bell();
			break;

		case RDP_DATA_PDU_LOGON:
			DEBUG(("Received Logon PDU\n"));
			/* User logged on */
			process_pdu_logon(s);
			break;

		case RDP_DATA_PDU_DISCONNECT:
			process_disconnect_pdu(s, ext_disc_reason);

			/* We used to return true and disconnect immediately here, but
			 * Windows Vista sends a disconnect PDU with reason 0 when
			 * reconnecting to a disconnected session, and MSTSC doesn't
			 * drop the connection.  I think we should just save the status.
			 */
			break;

		case RDP_DATA_PDU_AUTORECONNECT_STATUS:
			warning("Automatic reconnect using cookie, failed.\n");
			break;

		default:
			unimpl("data PDU %d\n", data_pdu_type);
	}
	return False;
}