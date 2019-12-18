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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 size_t RTA_TABLE ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static inline u32 rtm_get_table(struct nlattr *attrs[], u8 table)
{
	if (attrs[RTA_TABLE])
		table = nla_get_u32(attrs[RTA_TABLE]);

	return table;
}