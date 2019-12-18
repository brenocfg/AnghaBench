#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int first_received; int /*<<< orphan*/  init_mutex; scalar_t__ start_ts; scalar_t__ offset_usec; int /*<<< orphan*/ * paired_encoder; TYPE_2__ context; TYPE_1__ info; } ;
typedef  TYPE_3__ obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void obs_encoder_shutdown(obs_encoder_t *encoder)
{
	pthread_mutex_lock(&encoder->init_mutex);
	if (encoder->context.data) {
		encoder->info.destroy(encoder->context.data);
		encoder->context.data = NULL;
		encoder->paired_encoder = NULL;
		encoder->first_received = false;
		encoder->offset_usec = 0;
		encoder->start_ts = 0;
	}
	pthread_mutex_unlock(&encoder->init_mutex);
}