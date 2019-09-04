#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lpfc_hbq_init {int /*<<< orphan*/  seqlenoff; int /*<<< orphan*/  maxlen; int /*<<< orphan*/  seqlenbcnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  seqlenoff; int /*<<< orphan*/  maxlen; int /*<<< orphan*/  seqlenbcnt; } ;
struct TYPE_4__ {TYPE_1__ profile2; } ;
struct config_hbq_var {TYPE_2__ profiles; } ;

/* Variables and functions */

__attribute__((used)) static void
lpfc_build_hbq_profile2(struct config_hbq_var *hbqmb,
			struct lpfc_hbq_init  *hbq_desc)
{
	hbqmb->profiles.profile2.seqlenbcnt = hbq_desc->seqlenbcnt;
	hbqmb->profiles.profile2.maxlen     = hbq_desc->maxlen;
	hbqmb->profiles.profile2.seqlenoff  = hbq_desc->seqlenoff;
}