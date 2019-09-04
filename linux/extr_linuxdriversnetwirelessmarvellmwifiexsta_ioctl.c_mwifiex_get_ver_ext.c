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
typedef  int /*<<< orphan*/  ver_ext ;
typedef  int /*<<< orphan*/  u32 ;
struct mwifiex_ver_ext {int /*<<< orphan*/  version_str_sel; } ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_ACT_GEN_GET ; 
 int /*<<< orphan*/  HostCmd_CMD_VERSION_EXT ; 
 int /*<<< orphan*/  memset (struct mwifiex_ver_ext*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_ver_ext*,int) ; 

int
mwifiex_get_ver_ext(struct mwifiex_private *priv, u32 version_str_sel)
{
	struct mwifiex_ver_ext ver_ext;

	memset(&ver_ext, 0, sizeof(ver_ext));
	ver_ext.version_str_sel = version_str_sel;
	if (mwifiex_send_cmd(priv, HostCmd_CMD_VERSION_EXT,
			     HostCmd_ACT_GEN_GET, 0, &ver_ext, true))
		return -1;

	return 0;
}