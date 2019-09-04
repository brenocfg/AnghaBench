#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct raw3270_view {int dummy; } ;
struct fs3270 {scalar_t__ rdbuf_size; int active; TYPE_2__* init; TYPE_5__* rdbuf; } ;
struct TYPE_12__ {char** data; } ;
struct TYPE_10__ {scalar_t__ count; } ;
struct TYPE_11__ {int rc; int /*<<< orphan*/  (* callback ) (TYPE_2__*,int /*<<< orphan*/ *) ;scalar_t__ rescnt; TYPE_1__ ccw; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_EWRITEA ; 
 char TO_IC ; 
 char TO_SBA ; 
 char TW_KR ; 
 int /*<<< orphan*/  fs3270_reset_callback (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs3270_restore_callback (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw3270_request_final (TYPE_2__*) ; 
 int /*<<< orphan*/  raw3270_request_set_cmd (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3270_request_set_idal (TYPE_2__*,TYPE_5__*) ; 
 int raw3270_start_locked (struct raw3270_view*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fs3270_activate(struct raw3270_view *view)
{
	struct fs3270 *fp;
	char *cp;
	int rc;

	fp = (struct fs3270 *) view;

	/* If an old init command is still running just return. */
	if (!raw3270_request_final(fp->init))
		return 0;

	if (fp->rdbuf_size == 0) {
		/* No saved buffer. Just clear the screen. */
		raw3270_request_set_cmd(fp->init, TC_EWRITEA);
		fp->init->callback = fs3270_reset_callback;
	} else {
		/* Restore fullscreen buffer saved by fs3270_deactivate. */
		raw3270_request_set_cmd(fp->init, TC_EWRITEA);
		raw3270_request_set_idal(fp->init, fp->rdbuf);
		fp->init->ccw.count = fp->rdbuf_size;
		cp = fp->rdbuf->data[0];
		cp[0] = TW_KR;
		cp[1] = TO_SBA;
		cp[2] = cp[6];
		cp[3] = cp[7];
		cp[4] = TO_IC;
		cp[5] = TO_SBA;
		cp[6] = 0x40;
		cp[7] = 0x40;
		fp->init->rescnt = 0;
		fp->init->callback = fs3270_restore_callback;
	}
	rc = fp->init->rc = raw3270_start_locked(view, fp->init);
	if (rc)
		fp->init->callback(fp->init, NULL);
	else
		fp->active = 1;
	return rc;
}