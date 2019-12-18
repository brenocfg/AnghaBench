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
struct coreaudio_data {int au_initialized; int /*<<< orphan*/ * buf_list; int /*<<< orphan*/ * unit; } ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AudioComponentInstanceDispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AudioUnitUninitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ca_success (int /*<<< orphan*/ ,struct coreaudio_data*,char*,char*) ; 
 int /*<<< orphan*/  coreaudio_remove_hooks (struct coreaudio_data*) ; 
 int /*<<< orphan*/  coreaudio_stop (struct coreaudio_data*) ; 

__attribute__((used)) static void coreaudio_uninit(struct coreaudio_data *ca)
{
	if (!ca->au_initialized)
		return;

	if (ca->unit) {
		coreaudio_stop(ca);

		OSStatus stat = AudioUnitUninitialize(ca->unit);
		ca_success(stat, ca, "coreaudio_uninit", "uninitialize");

		coreaudio_remove_hooks(ca);

		stat = AudioComponentInstanceDispose(ca->unit);
		ca_success(stat, ca, "coreaudio_uninit", "dispose");

		ca->unit = NULL;
	}

	ca->au_initialized = false;

	buf_list_free(ca->buf_list);
	ca->buf_list = NULL;
}