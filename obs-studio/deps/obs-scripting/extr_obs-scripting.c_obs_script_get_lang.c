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
struct TYPE_4__ {int type; } ;
typedef  TYPE_1__ obs_script_t ;
typedef  enum obs_script_lang { ____Placeholder_obs_script_lang } obs_script_lang ;

/* Variables and functions */
 int OBS_SCRIPT_LANG_UNKNOWN ; 
 scalar_t__ ptr_valid (TYPE_1__ const*) ; 

enum obs_script_lang obs_script_get_lang(const obs_script_t *script)
{
	return ptr_valid(script) ? script->type : OBS_SCRIPT_LANG_UNKNOWN;
}