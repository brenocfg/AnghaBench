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
typedef  int /*<<< orphan*/  substring_t ;
struct nfs_parsed_mount_data {int version; int minorversion; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_MOUNT_VER3 ; 
#define  Opt_vers_2 133 
#define  Opt_vers_3 132 
#define  Opt_vers_4 131 
#define  Opt_vers_4_0 130 
#define  Opt_vers_4_1 129 
#define  Opt_vers_4_2 128 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_vers_tokens ; 

__attribute__((used)) static int nfs_parse_version_string(char *string,
		struct nfs_parsed_mount_data *mnt,
		substring_t *args)
{
	mnt->flags &= ~NFS_MOUNT_VER3;
	switch (match_token(string, nfs_vers_tokens, args)) {
	case Opt_vers_2:
		mnt->version = 2;
		break;
	case Opt_vers_3:
		mnt->flags |= NFS_MOUNT_VER3;
		mnt->version = 3;
		break;
	case Opt_vers_4:
		/* Backward compatibility option. In future,
		 * the mount program should always supply
		 * a NFSv4 minor version number.
		 */
		mnt->version = 4;
		break;
	case Opt_vers_4_0:
		mnt->version = 4;
		mnt->minorversion = 0;
		break;
	case Opt_vers_4_1:
		mnt->version = 4;
		mnt->minorversion = 1;
		break;
	case Opt_vers_4_2:
		mnt->version = 4;
		mnt->minorversion = 2;
		break;
	default:
		return 0;
	}
	return 1;
}