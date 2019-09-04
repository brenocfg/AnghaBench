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
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOOK2MANIP (unsigned int) ; 
 unsigned int __nf_nat_alloc_null_binding (struct nf_conn*,int /*<<< orphan*/ ) ; 

unsigned int
nf_nat_alloc_null_binding(struct nf_conn *ct, unsigned int hooknum)
{
	return __nf_nat_alloc_null_binding(ct, HOOK2MANIP(hooknum));
}