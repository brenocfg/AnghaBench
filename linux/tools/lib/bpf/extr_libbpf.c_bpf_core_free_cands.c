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
struct ids_vec {struct ids_vec* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ids_vec*) ; 

__attribute__((used)) static void bpf_core_free_cands(struct ids_vec *cand_ids)
{
	free(cand_ids->data);
	free(cand_ids);
}