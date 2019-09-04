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
typedef  int /*<<< orphan*/  uint32_t ;
struct obs_encoder_info {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 struct obs_encoder_info* find_encoder (char const*) ; 

uint32_t obs_get_encoder_caps(const char *encoder_id)
{
	struct obs_encoder_info *info = find_encoder(encoder_id);
	return info ? info->caps : 0;
}