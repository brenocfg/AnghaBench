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
 int __ubifs_node_insert_hmac (struct ubifs_info const*,void*,int,int) ; 
 scalar_t__ ubifs_authenticated (struct ubifs_info const*) ; 

__attribute__((used)) static inline int ubifs_node_insert_hmac(const struct ubifs_info *c, void *buf,
					  int len, int ofs_hmac)
{
	if (ubifs_authenticated(c))
		return __ubifs_node_insert_hmac(c, buf, len, ofs_hmac);
	else
		return 0;
}