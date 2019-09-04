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
struct seg6_local_lwt {int /*<<< orphan*/  oif; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 size_t SEG6_LOCAL_OIF ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static int parse_nla_oif(struct nlattr **attrs, struct seg6_local_lwt *slwt)
{
	slwt->oif = nla_get_u32(attrs[SEG6_LOCAL_OIF]);

	return 0;
}