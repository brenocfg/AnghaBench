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
struct net {int dummy; } ;

/* Variables and functions */
 unsigned int fib6_rules_seq_read (struct net*) ; 
 unsigned int fib6_tables_seq_read (struct net*) ; 

__attribute__((used)) static unsigned int fib6_seq_read(struct net *net)
{
	return fib6_tables_seq_read(net) + fib6_rules_seq_read(net);
}