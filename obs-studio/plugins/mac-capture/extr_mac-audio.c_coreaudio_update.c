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
struct coreaudio_data {int /*<<< orphan*/  device_uid; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coreaudio_shutdown (struct coreaudio_data*) ; 
 int /*<<< orphan*/  coreaudio_try_init (struct coreaudio_data*) ; 
 int /*<<< orphan*/  obs_data_get_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void coreaudio_update(void *data, obs_data_t *settings)
{
	struct coreaudio_data *ca = data;

	coreaudio_shutdown(ca);

	bfree(ca->device_uid);
	ca->device_uid = bstrdup(obs_data_get_string(settings, "device_id"));

	coreaudio_try_init(ca);
}