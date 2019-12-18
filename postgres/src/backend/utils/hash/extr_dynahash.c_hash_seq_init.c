#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * curEntry; scalar_t__ curBucket; TYPE_1__* hashp; } ;
struct TYPE_6__ {int /*<<< orphan*/  frozen; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__ HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  register_seq_scan (TYPE_1__*) ; 

void
hash_seq_init(HASH_SEQ_STATUS *status, HTAB *hashp)
{
	status->hashp = hashp;
	status->curBucket = 0;
	status->curEntry = NULL;
	if (!hashp->frozen)
		register_seq_scan(hashp);
}