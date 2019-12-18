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
 int /*<<< orphan*/  ubifs_add_dirt (struct ubifs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_auth_node_sz (struct ubifs_info*) ; 
 scalar_t__ ubifs_authenticated (struct ubifs_info*) ; 

__attribute__((used)) static void ubifs_add_auth_dirt(struct ubifs_info *c, int lnum)
{
	if (ubifs_authenticated(c))
		ubifs_add_dirt(c, lnum, ubifs_auth_node_sz(c));
}