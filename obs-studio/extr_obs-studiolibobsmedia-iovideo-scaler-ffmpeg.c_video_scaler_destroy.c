#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  swscale; } ;
typedef  TYPE_1__ video_scaler_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ ) ; 

void video_scaler_destroy(video_scaler_t *scaler)
{
	if (scaler) {
		sws_freeContext(scaler->swscale);
		bfree(scaler);
	}
}