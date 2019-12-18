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
struct ubifs_info {int hmac_desc_len; } ;
struct ubifs_auth_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ ubifs_authenticated (struct ubifs_info const*) ; 

__attribute__((used)) static inline int ubifs_auth_node_sz(const struct ubifs_info *c)
{
	if (ubifs_authenticated(c))
		return sizeof(struct ubifs_auth_node) + c->hmac_desc_len;
	else
		return 0;
}