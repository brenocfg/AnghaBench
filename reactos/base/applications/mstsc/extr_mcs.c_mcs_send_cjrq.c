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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int MCS_CJRQ ; 
 int /*<<< orphan*/  g_mcs_userid ; 
 int /*<<< orphan*/  iso_init (int) ; 
 int /*<<< orphan*/  iso_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mcs_send_cjrq(uint16 chanid)
{
	STREAM s;

	DEBUG_RDP5(("Sending CJRQ for channel #%d\n", chanid));

	s = iso_init(5);

	out_uint8(s, (MCS_CJRQ << 2));
	out_uint16_be(s, g_mcs_userid);
	out_uint16_be(s, chanid);

	s_mark_end(s);
	iso_send(s);
}