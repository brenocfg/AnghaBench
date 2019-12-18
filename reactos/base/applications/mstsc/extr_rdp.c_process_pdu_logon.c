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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 scalar_t__ INFOTYPE_LOGON_EXTENDED_INF ; 
 scalar_t__ LOGON_EX_AUTORECONNECTCOOKIE ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  g_has_reconnect_random ; 
 scalar_t__ g_reconnect_logonid ; 
 int /*<<< orphan*/  g_reconnect_random ; 
 int /*<<< orphan*/  g_reconnect_random_ts ; 
 int /*<<< orphan*/  in_uint32_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  in_uint8a (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (char*) ; 

void
process_pdu_logon(STREAM s)
{
	uint32 infotype;
	in_uint32_le(s, infotype);
	if (infotype == INFOTYPE_LOGON_EXTENDED_INF)
	{
		uint32 fieldspresent;

		in_uint8s(s, 2);	/* Length */
		in_uint32_le(s, fieldspresent);
		if (fieldspresent & LOGON_EX_AUTORECONNECTCOOKIE)
		{
			uint32 len;
			uint32 version;

			/* TS_LOGON_INFO_FIELD */
			in_uint8s(s, 4);	/* cbFieldData */

			/* ARC_SC_PRIVATE_PACKET */
			in_uint32_le(s, len);
			if (len != 28)
			{
				warning("Invalid length in Auto-Reconnect packet\n");
				return;
			}

			in_uint32_le(s, version);
			if (version != 1)
			{
				warning("Unsupported version of Auto-Reconnect packet\n");
				return;
			}

			in_uint32_le(s, g_reconnect_logonid);
			in_uint8a(s, g_reconnect_random, 16);
			g_has_reconnect_random = True;
			g_reconnect_random_ts = time(NULL);
			DEBUG(("Saving auto-reconnect cookie, id=%u\n", g_reconnect_logonid));
		}
	}
}