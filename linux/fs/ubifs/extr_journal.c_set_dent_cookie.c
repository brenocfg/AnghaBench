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
struct ubifs_info {scalar_t__ double_hash; } ;
struct ubifs_dent_node {scalar_t__ cookie; } ;

/* Variables and functions */
 scalar_t__ prandom_u32 () ; 

__attribute__((used)) static void set_dent_cookie(struct ubifs_info *c, struct ubifs_dent_node *dent)
{
	if (c->double_hash)
		dent->cookie = prandom_u32();
	else
		dent->cookie = 0;
}