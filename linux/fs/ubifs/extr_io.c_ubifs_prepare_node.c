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
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubifs_prepare_node_hmac (struct ubifs_info*,void*,int,int /*<<< orphan*/ ,int) ; 

void ubifs_prepare_node(struct ubifs_info *c, void *node, int len, int pad)
{
	/*
	 * Deliberately ignore return value since this function can only fail
	 * when a hmac offset is given.
	 */
	ubifs_prepare_node_hmac(c, node, len, 0, pad);
}