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
typedef  int /*<<< orphan*/  uint16_t ;
struct lbtf_private {int dummy; } ;
struct cmd_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBTF_DEB_CMD ; 
 int /*<<< orphan*/  __lbtf_cmd_async (struct lbtf_private*,int /*<<< orphan*/ ,struct cmd_header*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 

void lbtf_cmd_async(struct lbtf_private *priv, uint16_t command,
	struct cmd_header *in_cmd, int in_cmd_size)
{
	lbtf_deb_enter(LBTF_DEB_CMD);
	__lbtf_cmd_async(priv, command, in_cmd, in_cmd_size, NULL, 0);
	lbtf_deb_leave(LBTF_DEB_CMD);
}