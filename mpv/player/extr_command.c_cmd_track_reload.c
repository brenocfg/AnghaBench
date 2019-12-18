#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct track {int /*<<< orphan*/  type; scalar_t__ external_filename; scalar_t__ is_external; } ;
struct mp_cmd_ctx {int success; TYPE_3__* abort; TYPE_2__* args; scalar_t__ priv; struct MPContext* mpctx; } ;
struct MPContext {struct track** tracks; int /*<<< orphan*/  playback_initialized; } ;
struct TYPE_6__ {int /*<<< orphan*/  cancel; } ;
struct TYPE_4__ {int /*<<< orphan*/  i; } ;
struct TYPE_5__ {TYPE_1__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*) ; 
 int mp_add_external_file (struct MPContext*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_remove_track (struct MPContext*,struct track*) ; 
 int /*<<< orphan*/  mp_switch_track (struct MPContext*,int /*<<< orphan*/ ,struct track*,int /*<<< orphan*/ ) ; 
 struct track* mp_track_by_tid (struct MPContext*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_track_list (struct MPContext*,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void cmd_track_reload(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;
    int type = *(int *)cmd->priv;

    if (!mpctx->playback_initialized) {
        MP_ERR(mpctx, "Cannot reload while not initialized.\n");
        cmd->success = false;
        return;
    }

    struct track *t = mp_track_by_tid(mpctx, type, cmd->args[0].v.i);
    int nt_num = -1;

    if (t && t->is_external && t->external_filename) {
        char *filename = talloc_strdup(NULL, t->external_filename);
        mp_remove_track(mpctx, t);
        nt_num = mp_add_external_file(mpctx, filename, type, cmd->abort->cancel);
        talloc_free(filename);
    }

    if (nt_num < 0) {
        cmd->success = false;
        return;
    }

    struct track *nt = mpctx->tracks[nt_num];
    mp_switch_track(mpctx, nt->type, nt, 0);
    print_track_list(mpctx, "Reloaded:");
}