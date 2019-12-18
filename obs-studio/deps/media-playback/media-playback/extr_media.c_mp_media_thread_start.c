#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* stop_cb ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mp_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_media_thread (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *mp_media_thread_start(void *opaque)
{
	mp_media_t *m = opaque;

	if (!mp_media_thread(m)) {
		if (m->stop_cb) {
			m->stop_cb(m->opaque);
		}
	}

	return NULL;
}