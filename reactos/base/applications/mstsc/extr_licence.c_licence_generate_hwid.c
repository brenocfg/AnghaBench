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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 scalar_t__ LICENCE_HWID_SIZE ; 
 int /*<<< orphan*/  buf_out_uint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_hostname ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
licence_generate_hwid(uint8 * hwid)
{
	buf_out_uint32(hwid, 2);
	strncpy((char *) (hwid + 4), g_hostname, LICENCE_HWID_SIZE - 4);
}