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
struct obs_encoder_info {int type; } ;
typedef  enum obs_encoder_type { ____Placeholder_obs_encoder_type } obs_encoder_type ;

/* Variables and functions */
 int OBS_ENCODER_AUDIO ; 
 struct obs_encoder_info* find_encoder (char const*) ; 

enum obs_encoder_type obs_get_encoder_type(const char *id)
{
	struct obs_encoder_info *info = find_encoder(id);
	return info ? info->type : OBS_ENCODER_AUDIO;
}