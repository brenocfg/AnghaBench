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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum codespace_sel { ____Placeholder_codespace_sel } codespace_sel ;

/* Variables and functions */
 int enum_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

int imx_media_enum_mbus_format(u32 *code, u32 index, enum codespace_sel cs_sel,
			       bool allow_bayer)
{
	return enum_format(NULL, code, index, cs_sel, false, allow_bayer);
}