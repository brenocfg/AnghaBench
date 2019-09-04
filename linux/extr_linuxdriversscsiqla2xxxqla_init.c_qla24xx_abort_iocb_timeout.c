#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  comp_status; } ;
struct TYPE_8__ {TYPE_2__ abt; } ;
struct srb_iocb {TYPE_3__ u; } ;
struct TYPE_6__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* done ) (TYPE_4__*,int /*<<< orphan*/ ) ;TYPE_1__ u; } ;
typedef  TYPE_4__ srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_TIMEOUT ; 
 int /*<<< orphan*/  QLA_FUNCTION_TIMEOUT ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla24xx_abort_iocb_timeout(void *data)
{
	srb_t *sp = data;
	struct srb_iocb *abt = &sp->u.iocb_cmd;

	abt->u.abt.comp_status = CS_TIMEOUT;
	sp->done(sp, QLA_FUNCTION_TIMEOUT);
}