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
struct lbs_private {int dummy; } ;
struct cmd_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lbs_cmd_async (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_header*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_cmd_async_callback ; 

void lbs_cmd_async(struct lbs_private *priv, uint16_t command,
	struct cmd_header *in_cmd, int in_cmd_size)
{
	__lbs_cmd_async(priv, command, in_cmd, in_cmd_size,
		lbs_cmd_async_callback, 0);
}