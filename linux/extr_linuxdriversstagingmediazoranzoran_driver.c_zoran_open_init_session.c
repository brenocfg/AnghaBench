#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* active; scalar_t__ allocated; TYPE_3__* buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  format; scalar_t__ is_set; } ;
struct zoran_fh {TYPE_4__ buffers; int /*<<< orphan*/  jpg_settings; int /*<<< orphan*/  v4l_settings; void* overlay_active; TYPE_1__ overlay_settings; struct zoran* zr; } ;
struct zoran {int /*<<< orphan*/  jpg_settings; int /*<<< orphan*/  v4l_settings; TYPE_1__ overlay_settings; } ;
struct TYPE_6__ {int frame; } ;
struct TYPE_7__ {TYPE_2__ bs; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUZ_STATE_USER ; 
 int MAX_FRAME ; 
 void* ZORAN_FREE ; 
 int /*<<< orphan*/  map_mode_raw (struct zoran_fh*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zoran_open_init_session(struct zoran_fh *fh)
{
	int i;
	struct zoran *zr = fh->zr;

	/* Per default, map the V4L Buffers */
	map_mode_raw(fh);

	/* take over the card's current settings */
	fh->overlay_settings = zr->overlay_settings;
	fh->overlay_settings.is_set = 0;
	fh->overlay_settings.format = zr->overlay_settings.format;
	fh->overlay_active = ZORAN_FREE;

	/* v4l settings */
	fh->v4l_settings = zr->v4l_settings;
	/* jpg settings */
	fh->jpg_settings = zr->jpg_settings;

	/* buffers */
	memset(&fh->buffers, 0, sizeof(fh->buffers));
	for (i = 0; i < MAX_FRAME; i++) {
		fh->buffers.buffer[i].state = BUZ_STATE_USER;	/* nothing going on */
		fh->buffers.buffer[i].bs.frame = i;
	}
	fh->buffers.allocated = 0;
	fh->buffers.active = ZORAN_FREE;
}