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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int ISO_PDU_CR ; 
 int RDP_NEG_REQ ; 
 scalar_t__ RDP_V5 ; 
 scalar_t__ g_negotiate_rdp_protocol ; 
 scalar_t__ g_rdp_version ; 
 int /*<<< orphan*/  out_uint16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint16_be (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8p (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tcp_init (int) ; 
 int /*<<< orphan*/  tcp_send (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iso_send_connection_request(char *username, uint32 neg_proto)
{
	STREAM s;
	int length = 30 + strlen(username);

	if (g_rdp_version >= RDP_V5 && g_negotiate_rdp_protocol)
		length += 8;

	s = tcp_init(length);

	out_uint8(s, 3);	/* version */
	out_uint8(s, 0);	/* reserved */
	out_uint16_be(s, length);	/* length */

	out_uint8(s, length - 5);	/* hdrlen */
	out_uint8(s, ISO_PDU_CR);
	out_uint16(s, 0);	/* dst_ref */
	out_uint16(s, 0);	/* src_ref */
	out_uint8(s, 0);	/* class */

	out_uint8p(s, "Cookie: mstshash=", strlen("Cookie: mstshash="));
	out_uint8p(s, username, strlen(username));

	out_uint8(s, 0x0d);	/* cookie termination string: CR+LF */
	out_uint8(s, 0x0a);

	if (g_rdp_version >= RDP_V5 && g_negotiate_rdp_protocol)
	{
		/* optional rdp protocol negotiation request for RDPv5 */
		out_uint8(s, RDP_NEG_REQ);
		out_uint8(s, 0);
		out_uint16(s, 8);
		out_uint32(s, neg_proto);
	}

	s_mark_end(s);
	tcp_send(s);
}