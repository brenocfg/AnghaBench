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
typedef  int u16 ;
struct tomoyo_acl_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TOMOYO_MAC_FILE_MOUNT ; 
 size_t TOMOYO_MAX_MKDEV_OPERATION ; 
 size_t TOMOYO_MAX_PATH2_OPERATION ; 
 size_t TOMOYO_MAX_PATH_NUMBER_OPERATION ; 
 size_t TOMOYO_MAX_PATH_OPERATION ; 
 int /*<<< orphan*/ * tomoyo_mac_keywords ; 
 int /*<<< orphan*/ * tomoyo_path_keyword ; 
 scalar_t__ tomoyo_permstr (char const*,int /*<<< orphan*/ ) ; 
 size_t* tomoyo_pn2mac ; 
 size_t* tomoyo_pnnn2mac ; 
 size_t* tomoyo_pp2mac ; 
 char* tomoyo_read_token (struct tomoyo_acl_param*) ; 
 int tomoyo_update_mkdev_acl (int,struct tomoyo_acl_param*) ; 
 int tomoyo_update_mount_acl (struct tomoyo_acl_param*) ; 
 int tomoyo_update_path2_acl (int,struct tomoyo_acl_param*) ; 
 int tomoyo_update_path_acl (int,struct tomoyo_acl_param*) ; 
 int tomoyo_update_path_number_acl (int,struct tomoyo_acl_param*) ; 

int tomoyo_write_file(struct tomoyo_acl_param *param)
{
	u16 perm = 0;
	u8 type;
	const char *operation = tomoyo_read_token(param);

	for (type = 0; type < TOMOYO_MAX_PATH_OPERATION; type++)
		if (tomoyo_permstr(operation, tomoyo_path_keyword[type]))
			perm |= 1 << type;
	if (perm)
		return tomoyo_update_path_acl(perm, param);
	for (type = 0; type < TOMOYO_MAX_PATH2_OPERATION; type++)
		if (tomoyo_permstr(operation,
				   tomoyo_mac_keywords[tomoyo_pp2mac[type]]))
			perm |= 1 << type;
	if (perm)
		return tomoyo_update_path2_acl(perm, param);
	for (type = 0; type < TOMOYO_MAX_PATH_NUMBER_OPERATION; type++)
		if (tomoyo_permstr(operation,
				   tomoyo_mac_keywords[tomoyo_pn2mac[type]]))
			perm |= 1 << type;
	if (perm)
		return tomoyo_update_path_number_acl(perm, param);
	for (type = 0; type < TOMOYO_MAX_MKDEV_OPERATION; type++)
		if (tomoyo_permstr(operation,
				   tomoyo_mac_keywords[tomoyo_pnnn2mac[type]]))
			perm |= 1 << type;
	if (perm)
		return tomoyo_update_mkdev_acl(perm, param);
	if (tomoyo_permstr(operation,
			   tomoyo_mac_keywords[TOMOYO_MAC_FILE_MOUNT]))
		return tomoyo_update_mount_acl(param);
	return -EINVAL;
}