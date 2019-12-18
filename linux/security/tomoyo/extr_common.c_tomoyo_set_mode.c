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
typedef  size_t u8 ;
struct tomoyo_profile {size_t default_config; size_t* config; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TOMOYO_CONFIG_USE_DEFAULT ; 
 size_t TOMOYO_CONFIG_WANT_GRANT_LOG ; 
 size_t TOMOYO_CONFIG_WANT_REJECT_LOG ; 
 size_t TOMOYO_MAX_MAC_CATEGORY_INDEX ; 
 size_t TOMOYO_MAX_MAC_INDEX ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 scalar_t__ strstr (char const*,char*) ; 
 char** tomoyo_category_keywords ; 
 int tomoyo_find_yesno (char const*,char*) ; 
 size_t* tomoyo_index2category ; 
 char** tomoyo_mac_keywords ; 
 char** tomoyo_mode ; 
 scalar_t__ tomoyo_str_starts (char**,char*) ; 

__attribute__((used)) static int tomoyo_set_mode(char *name, const char *value,
			   struct tomoyo_profile *profile)
{
	u8 i;
	u8 config;

	if (!strcmp(name, "CONFIG")) {
		i = TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGORY_INDEX;
		config = profile->default_config;
	} else if (tomoyo_str_starts(&name, "CONFIG::")) {
		config = 0;
		for (i = 0; i < TOMOYO_MAX_MAC_INDEX
			     + TOMOYO_MAX_MAC_CATEGORY_INDEX; i++) {
			int len = 0;

			if (i < TOMOYO_MAX_MAC_INDEX) {
				const u8 c = tomoyo_index2category[i];
				const char *category =
					tomoyo_category_keywords[c];

				len = strlen(category);
				if (strncmp(name, category, len) ||
				    name[len++] != ':' || name[len++] != ':')
					continue;
			}
			if (strcmp(name + len, tomoyo_mac_keywords[i]))
				continue;
			config = profile->config[i];
			break;
		}
		if (i == TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGORY_INDEX)
			return -EINVAL;
	} else {
		return -EINVAL;
	}
	if (strstr(value, "use_default")) {
		config = TOMOYO_CONFIG_USE_DEFAULT;
	} else {
		u8 mode;

		for (mode = 0; mode < 4; mode++)
			if (strstr(value, tomoyo_mode[mode]))
				/*
				 * Update lower 3 bits in order to distinguish
				 * 'config' from 'TOMOYO_CONFIG_USE_DEAFULT'.
				 */
				config = (config & ~7) | mode;
		if (config != TOMOYO_CONFIG_USE_DEFAULT) {
			switch (tomoyo_find_yesno(value, "grant_log")) {
			case 1:
				config |= TOMOYO_CONFIG_WANT_GRANT_LOG;
				break;
			case 0:
				config &= ~TOMOYO_CONFIG_WANT_GRANT_LOG;
				break;
			}
			switch (tomoyo_find_yesno(value, "reject_log")) {
			case 1:
				config |= TOMOYO_CONFIG_WANT_REJECT_LOG;
				break;
			case 0:
				config &= ~TOMOYO_CONFIG_WANT_REJECT_LOG;
				break;
			}
		}
	}
	if (i < TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGORY_INDEX)
		profile->config[i] = config;
	else if (config != TOMOYO_CONFIG_USE_DEFAULT)
		profile->default_config = config;
	return 0;
}