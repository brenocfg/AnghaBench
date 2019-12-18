#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  space_peak; int /*<<< orphan*/  nbatch_original; int /*<<< orphan*/  nbatch; int /*<<< orphan*/  nbuckets_original; int /*<<< orphan*/  nbuckets; } ;
struct TYPE_5__ {int /*<<< orphan*/  spacePeak; int /*<<< orphan*/  nbatch_original; int /*<<< orphan*/  nbatch; int /*<<< orphan*/  nbuckets_original; int /*<<< orphan*/  nbuckets; } ;
typedef  TYPE_1__* HashJoinTable ;
typedef  TYPE_2__ HashInstrumentation ;

/* Variables and functions */

void
ExecHashGetInstrumentation(HashInstrumentation *instrument,
						   HashJoinTable hashtable)
{
	instrument->nbuckets = hashtable->nbuckets;
	instrument->nbuckets_original = hashtable->nbuckets_original;
	instrument->nbatch = hashtable->nbatch;
	instrument->nbatch_original = hashtable->nbatch_original;
	instrument->space_peak = hashtable->spacePeak;
}