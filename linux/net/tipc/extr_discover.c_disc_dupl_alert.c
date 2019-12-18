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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_media_addr {int dummy; } ;
struct tipc_bearer {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  media_addr_str ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_media_addr_printf (char*,int,struct tipc_media_addr*) ; 

__attribute__((used)) static void disc_dupl_alert(struct tipc_bearer *b, u32 node_addr,
			    struct tipc_media_addr *media_addr)
{
	char media_addr_str[64];

	tipc_media_addr_printf(media_addr_str, sizeof(media_addr_str),
			       media_addr);
	pr_warn("Duplicate %x using %s seen on <%s>\n", node_addr,
		media_addr_str, b->name);
}