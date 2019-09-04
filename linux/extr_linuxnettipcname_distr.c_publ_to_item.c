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
struct publication {int /*<<< orphan*/  key; int /*<<< orphan*/  port; int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; } ;
struct distr_item {void* key; void* port; void* upper; void* lower; void* type; } ;

/* Variables and functions */
 void* htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void publ_to_item(struct distr_item *i, struct publication *p)
{
	i->type = htonl(p->type);
	i->lower = htonl(p->lower);
	i->upper = htonl(p->upper);
	i->port = htonl(p->port);
	i->key = htonl(p->key);
}