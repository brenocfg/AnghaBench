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
struct asd_seq_data {int num_edbs; int /*<<< orphan*/ * edb_arr; } ;
struct asd_ha_struct {struct asd_seq_data seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  asd_free_coherent (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asd_free_edbs(struct asd_ha_struct *asd_ha)
{
	struct asd_seq_data *seq = &asd_ha->seq;
	int i;

	for (i = 0; i < seq->num_edbs; i++)
		asd_free_coherent(asd_ha, seq->edb_arr[i]);
	kfree(seq->edb_arr);
	seq->edb_arr = NULL;
}