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
struct coreaudio_data {int au_initialized; int /*<<< orphan*/  device_name; int /*<<< orphan*/  unit; int /*<<< orphan*/  device_id; } ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AudioUnitInitialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_TYPE_INPUT ; 
 int /*<<< orphan*/  IO_TYPE_OUTPUT ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  SCOPE_GLOBAL ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ca_success (int /*<<< orphan*/ ,struct coreaudio_data*,char*,char*) ; 
 int /*<<< orphan*/  coreaudio_get_device_name (struct coreaudio_data*) ; 
 int /*<<< orphan*/  coreaudio_init_buffer (struct coreaudio_data*) ; 
 int /*<<< orphan*/  coreaudio_init_format (struct coreaudio_data*) ; 
 int /*<<< orphan*/  coreaudio_init_hooks (struct coreaudio_data*) ; 
 int /*<<< orphan*/  coreaudio_init_unit (struct coreaudio_data*) ; 
 int /*<<< orphan*/  coreaudio_start (struct coreaudio_data*) ; 
 int /*<<< orphan*/  coreaudio_uninit (struct coreaudio_data*) ; 
 int /*<<< orphan*/  enable_io (struct coreaudio_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  find_device_id_by_uid (struct coreaudio_data*) ; 
 int /*<<< orphan*/  kAudioOutputUnitProperty_CurrentDevice ; 
 int /*<<< orphan*/  set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool coreaudio_init(struct coreaudio_data *ca)
{
	OSStatus stat;

	if (ca->au_initialized)
		return true;

	if (!find_device_id_by_uid(ca))
		return false;
	if (!coreaudio_get_device_name(ca))
		return false;
	if (!coreaudio_init_unit(ca))
		return false;

	stat = enable_io(ca, IO_TYPE_INPUT, true);
	if (!ca_success(stat, ca, "coreaudio_init", "enable input io"))
		goto fail;

	stat = enable_io(ca, IO_TYPE_OUTPUT, false);
	if (!ca_success(stat, ca, "coreaudio_init", "disable output io"))
		goto fail;

	stat = set_property(ca->unit, kAudioOutputUnitProperty_CurrentDevice,
			    SCOPE_GLOBAL, 0, &ca->device_id,
			    sizeof(ca->device_id));
	if (!ca_success(stat, ca, "coreaudio_init", "set current device"))
		goto fail;

	if (!coreaudio_init_format(ca))
		goto fail;
	if (!coreaudio_init_buffer(ca))
		goto fail;
	if (!coreaudio_init_hooks(ca))
		goto fail;

	stat = AudioUnitInitialize(ca->unit);
	if (!ca_success(stat, ca, "coreaudio_initialize", "initialize"))
		goto fail;

	if (!coreaudio_start(ca))
		goto fail;

	blog(LOG_INFO, "coreaudio: device '%s' initialized", ca->device_name);
	return ca->au_initialized;

fail:
	coreaudio_uninit(ca);
	return false;
}