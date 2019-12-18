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
 int net_eq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 

__attribute__((used)) static int kill_all(struct nf_conn *i, void *data)
{
	return net_eq(nf_ct_net(i), data);
}