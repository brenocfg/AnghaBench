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
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_out_unistr (int /*<<< orphan*/ ,char*,int) ; 

void
rdp_out_unistr_mandatory_null(STREAM s, char *string, int len)
{
	if (string && len > 0)
		rdp_out_unistr(s, string, len);
	else
		out_uint16_le(s, 0);
}