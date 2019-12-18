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
struct MPContext {TYPE_1__* opts; } ;
struct TYPE_2__ {int /*<<< orphan*/ * record_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*) ; 
 int /*<<< orphan*/  close_recorder (struct MPContext*) ; 
 int /*<<< orphan*/  mp_notify_property (struct MPContext*,char*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 

void close_recorder_and_error(struct MPContext *mpctx)
{
    close_recorder(mpctx);
    talloc_free(mpctx->opts->record_file);
    mpctx->opts->record_file = NULL;
    mp_notify_property(mpctx, "record-file");
    MP_ERR(mpctx, "Disabling stream recording.\n");
}