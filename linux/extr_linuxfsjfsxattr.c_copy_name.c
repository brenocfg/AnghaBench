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
struct jfs_ea {int namelen; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  XATTR_OS2_PREFIX ; 
 int XATTR_OS2_PREFIX_LEN ; 
 int /*<<< orphan*/  is_known_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int copy_name(char *buffer, struct jfs_ea *ea)
{
	int len = ea->namelen;

	if (!is_known_namespace(ea->name)) {
		memcpy(buffer, XATTR_OS2_PREFIX, XATTR_OS2_PREFIX_LEN);
		buffer += XATTR_OS2_PREFIX_LEN;
		len += XATTR_OS2_PREFIX_LEN;
	}
	memcpy(buffer, ea->name, ea->namelen);
	buffer[ea->namelen] = 0;

	return len;
}