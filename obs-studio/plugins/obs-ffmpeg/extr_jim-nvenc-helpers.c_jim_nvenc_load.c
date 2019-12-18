#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  init_mutex ; 
 int /*<<< orphan*/  nvenc_info ; 
 int /*<<< orphan*/  obs_register_encoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void jim_nvenc_load(void)
{
	pthread_mutex_init(&init_mutex, NULL);
	obs_register_encoder(&nvenc_info);
}