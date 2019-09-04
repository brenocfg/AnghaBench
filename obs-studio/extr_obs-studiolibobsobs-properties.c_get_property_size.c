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
struct text_data {int dummy; } ;
struct path_data {int dummy; } ;
struct list_data {int dummy; } ;
struct int_data {int dummy; } ;
struct group_data {int dummy; } ;
struct frame_rate_data {int dummy; } ;
struct float_data {int dummy; } ;
struct editable_list_data {int dummy; } ;
struct button_data {int dummy; } ;
typedef  enum obs_property_type { ____Placeholder_obs_property_type } obs_property_type ;

/* Variables and functions */
#define  OBS_PROPERTY_BOOL 140 
#define  OBS_PROPERTY_BUTTON 139 
#define  OBS_PROPERTY_COLOR 138 
#define  OBS_PROPERTY_EDITABLE_LIST 137 
#define  OBS_PROPERTY_FLOAT 136 
#define  OBS_PROPERTY_FONT 135 
#define  OBS_PROPERTY_FRAME_RATE 134 
#define  OBS_PROPERTY_GROUP 133 
#define  OBS_PROPERTY_INT 132 
#define  OBS_PROPERTY_INVALID 131 
#define  OBS_PROPERTY_LIST 130 
#define  OBS_PROPERTY_PATH 129 
#define  OBS_PROPERTY_TEXT 128 

__attribute__((used)) static inline size_t get_property_size(enum obs_property_type type)
{
	switch (type) {
	case OBS_PROPERTY_INVALID:   return 0;
	case OBS_PROPERTY_BOOL:      return 0;
	case OBS_PROPERTY_INT:       return sizeof(struct int_data);
	case OBS_PROPERTY_FLOAT:     return sizeof(struct float_data);
	case OBS_PROPERTY_TEXT:      return sizeof(struct text_data);
	case OBS_PROPERTY_PATH:      return sizeof(struct path_data);
	case OBS_PROPERTY_LIST:      return sizeof(struct list_data);
	case OBS_PROPERTY_COLOR:     return 0;
	case OBS_PROPERTY_BUTTON:    return sizeof(struct button_data);
	case OBS_PROPERTY_FONT:      return 0;
	case OBS_PROPERTY_EDITABLE_LIST:
		return sizeof(struct editable_list_data);
	case OBS_PROPERTY_FRAME_RATE:return sizeof(struct frame_rate_data);
	case OBS_PROPERTY_GROUP:     return sizeof(struct group_data);
	}

	return 0;
}