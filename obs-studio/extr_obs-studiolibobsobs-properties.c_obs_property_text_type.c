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
struct text_data {int type; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  enum obs_text_type { ____Placeholder_obs_text_type } obs_text_type ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_PROPERTY_TEXT ; 
 int OBS_TEXT_DEFAULT ; 
 struct text_data* get_type_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum obs_text_type obs_property_text_type(obs_property_t *p)
{
	struct text_data *data = get_type_data(p, OBS_PROPERTY_TEXT);
	return data ? data->type : OBS_TEXT_DEFAULT;
}