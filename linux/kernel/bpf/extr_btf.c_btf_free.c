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
struct btf {int /*<<< orphan*/  data; int /*<<< orphan*/  resolved_ids; int /*<<< orphan*/  resolved_sizes; int /*<<< orphan*/  types; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct btf*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btf_free(struct btf *btf)
{
	kvfree(btf->types);
	kvfree(btf->resolved_sizes);
	kvfree(btf->resolved_ids);
	kvfree(btf->data);
	kfree(btf);
}