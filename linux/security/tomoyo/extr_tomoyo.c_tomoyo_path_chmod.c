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
typedef  int umode_t ;
struct path {int dummy; } ;

/* Variables and functions */
 int S_IALLUGO ; 
 int /*<<< orphan*/  TOMOYO_TYPE_CHMOD ; 
 int tomoyo_path_number_perm (int /*<<< orphan*/ ,struct path const*,int) ; 

__attribute__((used)) static int tomoyo_path_chmod(const struct path *path, umode_t mode)
{
	return tomoyo_path_number_perm(TOMOYO_TYPE_CHMOD, path,
				       mode & S_IALLUGO);
}