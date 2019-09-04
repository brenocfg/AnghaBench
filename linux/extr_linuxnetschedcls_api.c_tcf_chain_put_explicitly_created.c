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
struct tcf_chain {scalar_t__ explicitly_created; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcf_chain_put (struct tcf_chain*) ; 

__attribute__((used)) static void tcf_chain_put_explicitly_created(struct tcf_chain *chain)
{
	if (chain->explicitly_created)
		tcf_chain_put(chain);
}