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
struct mwifiex_private {int /*<<< orphan*/  version_str; } ;
struct host_cmd_ds_version_ext {int /*<<< orphan*/  version_str; int /*<<< orphan*/  version_str_sel; } ;
struct TYPE_2__ {struct host_cmd_ds_version_ext verext; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mwifiex_ret_ver_ext(struct mwifiex_private *priv,
			       struct host_cmd_ds_command *resp,
			       struct host_cmd_ds_version_ext *version_ext)
{
	struct host_cmd_ds_version_ext *ver_ext = &resp->params.verext;

	if (version_ext) {
		version_ext->version_str_sel = ver_ext->version_str_sel;
		memcpy(version_ext->version_str, ver_ext->version_str,
		       sizeof(char) * 128);
		memcpy(priv->version_str, ver_ext->version_str, 128);
	}
	return 0;
}