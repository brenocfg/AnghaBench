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
struct cmd_header {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct cmd_header*,struct cmd_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lbs_cmd_copyback(struct lbs_private *priv, unsigned long extra,
		     struct cmd_header *resp)
{
	struct cmd_header *buf = (void *)extra;
	uint16_t copy_len;

	copy_len = min(le16_to_cpu(buf->size), le16_to_cpu(resp->size));
	memcpy(buf, resp, copy_len);
	return 0;
}