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
typedef  int /*<<< orphan*/  obs_hotkey_id ;
typedef  int /*<<< orphan*/  obs_hotkey_func ;
struct TYPE_4__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_HOTKEY_REGISTERER_ENCODER ; 
 int /*<<< orphan*/  OBS_INVALID_HOTKEY_ID ; 
 int /*<<< orphan*/  lock () ; 
 int /*<<< orphan*/  obs_encoder_get_weak_encoder (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_hotkey_register_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  unlock () ; 

obs_hotkey_id obs_hotkey_register_encoder(obs_encoder_t *encoder,
					  const char *name,
					  const char *description,
					  obs_hotkey_func func, void *data)
{
	if (!encoder || !lock())
		return OBS_INVALID_HOTKEY_ID;

	obs_hotkey_id id = obs_hotkey_register_internal(
		OBS_HOTKEY_REGISTERER_ENCODER,
		obs_encoder_get_weak_encoder(encoder), &encoder->context, name,
		description, func, data);

	unlock();
	return id;
}