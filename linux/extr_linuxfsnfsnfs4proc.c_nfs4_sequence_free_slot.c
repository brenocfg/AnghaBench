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
struct nfs4_sequence_res {int /*<<< orphan*/ * sr_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs40_sequence_free_slot (struct nfs4_sequence_res*) ; 

__attribute__((used)) static void nfs4_sequence_free_slot(struct nfs4_sequence_res *res)
{
	if (res->sr_slot != NULL)
		nfs40_sequence_free_slot(res);
}