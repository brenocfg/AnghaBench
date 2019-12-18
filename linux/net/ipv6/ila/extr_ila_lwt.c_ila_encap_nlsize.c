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
typedef  int /*<<< orphan*/  u64 ;
struct lwtunnel_state {int dummy; } ;

/* Variables and functions */
 int nla_total_size (int) ; 
 int nla_total_size_64bit (int) ; 

__attribute__((used)) static int ila_encap_nlsize(struct lwtunnel_state *lwtstate)
{
	return nla_total_size_64bit(sizeof(u64)) + /* ILA_ATTR_LOCATOR */
	       nla_total_size(sizeof(u8)) +        /* ILA_ATTR_CSUM_MODE */
	       nla_total_size(sizeof(u8)) +        /* ILA_ATTR_IDENT_TYPE */
	       nla_total_size(sizeof(u8)) +        /* ILA_ATTR_HOOK_TYPE */
	       0;
}