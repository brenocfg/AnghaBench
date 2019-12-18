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
typedef  int uint32 ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 scalar_t__ RDP_V5 ; 
 int SEC_CC_REDIRECTION_SUPPORTED ; 
 int SEC_CC_REDIRECT_SESSIONID_FIELD_VALID ; 
 int SEC_CC_REDIRECT_VERSION_3 ; 
 int SEC_TAG_CLI_CHANNELS ; 
 int SEC_TAG_CLI_CLUSTER ; 
 int SEC_TAG_CLI_CRYPT ; 
 int SEC_TAG_CLI_INFO ; 
 TYPE_1__* g_channels ; 
 scalar_t__ g_console_session ; 
 scalar_t__ g_encryption ; 
 int g_height ; 
 int /*<<< orphan*/  g_hostname ; 
 int g_keyboard_functionkeys ; 
 int g_keyboard_subtype ; 
 int g_keyboard_type ; 
 int g_keylayout ; 
 int g_num_channels ; 
 scalar_t__ g_rdp_version ; 
 scalar_t__ g_redirect_session_id ; 
 int g_server_depth ; 
 int g_width ; 
 int /*<<< orphan*/  out_uint16_be (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  out_uint32_be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8a (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdp_out_unistr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sec_out_mcs_data(STREAM s, uint32 selected_protocol)
{
	int hostlen = 2 * strlen(g_hostname);
	int length = 162 + 76 + 12 + 4;
	unsigned int i;
	uint32 cluster_flags = 0;

	if (g_num_channels > 0)
		length += g_num_channels * 12 + 8;

	if (hostlen > 30)
		hostlen = 30;

	/* Generic Conference Control (T.124) ConferenceCreateRequest */
	out_uint16_be(s, 5);
	out_uint16_be(s, 0x14);
	out_uint8(s, 0x7c);
	out_uint16_be(s, 1);

	out_uint16_be(s, (length | 0x8000));	/* remaining length */

	out_uint16_be(s, 8);	/* length? */
	out_uint16_be(s, 16);
	out_uint8(s, 0);
	out_uint16_le(s, 0xc001);
	out_uint8(s, 0);

	out_uint32_le(s, 0x61637544);	/* OEM ID: "Duca", as in Ducati. */
	out_uint16_be(s, ((length - 14) | 0x8000));	/* remaining length */

	/* Client information */
	out_uint16_le(s, SEC_TAG_CLI_INFO);
	out_uint16_le(s, 216);	/* length */
	out_uint16_le(s, (g_rdp_version >= RDP_V5) ? 4 : 1);	/* RDP version. 1 == RDP4, 4 >= RDP5 to RDP8 */
	out_uint16_le(s, 8);
	out_uint16_le(s, g_width);
	out_uint16_le(s, g_height);
	out_uint16_le(s, 0xca01);
	out_uint16_le(s, 0xaa03);
	out_uint32_le(s, g_keylayout);
	out_uint32_le(s, 2600);	/* Client build. We are now 2600 compatible :-) */

	/* Unicode name of client, padded to 32 bytes */
	rdp_out_unistr(s, g_hostname, hostlen);
	out_uint8s(s, 30 - hostlen);

	/* See
	   http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wceddk40/html/cxtsksupportingremotedesktopprotocol.asp */
	out_uint32_le(s, g_keyboard_type);
	out_uint32_le(s, g_keyboard_subtype);
	out_uint32_le(s, g_keyboard_functionkeys);
	out_uint8s(s, 64);	/* reserved? 4 + 12 doublewords */
	out_uint16_le(s, 0xca01);	/* colour depth? */
	out_uint16_le(s, 1);

	out_uint32(s, 0);
	out_uint8(s, g_server_depth);
	out_uint16_le(s, 0x0700);
	out_uint8(s, 0);
	out_uint32_le(s, 1);
	out_uint8s(s, 64);
	out_uint32_le(s, selected_protocol);	/* End of client info */

	/* Write a Client Cluster Data (TS_UD_CS_CLUSTER) */
	out_uint16_le(s, SEC_TAG_CLI_CLUSTER);	/* header.type */
	out_uint16_le(s, 12);	/* length */

	cluster_flags |= SEC_CC_REDIRECTION_SUPPORTED;
	cluster_flags |= (SEC_CC_REDIRECT_VERSION_3 << 2);

	if (g_console_session || g_redirect_session_id != 0)
		cluster_flags |= SEC_CC_REDIRECT_SESSIONID_FIELD_VALID;

	out_uint32_le(s, cluster_flags);
	out_uint32(s, g_redirect_session_id);

	/* Client encryption settings */
	out_uint16_le(s, SEC_TAG_CLI_CRYPT);
	out_uint16_le(s, 12);	/* length */
	out_uint32_le(s, g_encryption ? 0x3 : 0);	/* encryption supported, 128-bit supported */
	out_uint32(s, 0);	/* Unknown */

	DEBUG_RDP5(("g_num_channels is %d\n", g_num_channels));
	if (g_num_channels > 0)
	{
		out_uint16_le(s, SEC_TAG_CLI_CHANNELS);
		out_uint16_le(s, g_num_channels * 12 + 8);	/* length */
		out_uint32_le(s, g_num_channels);	/* number of virtual channels */
		for (i = 0; i < g_num_channels; i++)
		{
			DEBUG_RDP5(("Requesting channel %s\n", g_channels[i].name));
			out_uint8a(s, g_channels[i].name, 8);
			out_uint32_be(s, g_channels[i].flags);
		}
	}

	s_mark_end(s);
}