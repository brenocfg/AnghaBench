#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  use; } ;
struct nf_conn {TYPE_1__ ct_general; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_kill (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 scalar_t__ nf_ct_should_gc (struct nf_conn*) ; 

__attribute__((used)) static void nf_ct_gc_expired(struct nf_conn *ct)
{
	if (!atomic_inc_not_zero(&ct->ct_general.use))
		return;

	if (nf_ct_should_gc(ct))
		nf_ct_kill(ct);

	nf_ct_put(ct);
}