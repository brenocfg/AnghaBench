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
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  in_uint32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
process_disconnect_pdu(STREAM s, uint32 * ext_disc_reason)
{
	in_uint32_le(s, *ext_disc_reason);

	DEBUG(("Received disconnect PDU\n"));
}