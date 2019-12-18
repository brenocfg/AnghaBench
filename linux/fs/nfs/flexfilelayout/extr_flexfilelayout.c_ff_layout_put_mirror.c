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
struct nfs4_ff_layout_mirror {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_layout_free_mirror (struct nfs4_ff_layout_mirror*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ff_layout_put_mirror(struct nfs4_ff_layout_mirror *mirror)
{
	if (mirror != NULL && refcount_dec_and_test(&mirror->ref))
		ff_layout_free_mirror(mirror);
}