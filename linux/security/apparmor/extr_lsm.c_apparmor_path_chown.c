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
struct path {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AA_MAY_CHOWN ; 
 int /*<<< orphan*/  OP_CHOWN ; 
 int common_perm_cond (int /*<<< orphan*/ ,struct path const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apparmor_path_chown(const struct path *path, kuid_t uid, kgid_t gid)
{
	return common_perm_cond(OP_CHOWN, path, AA_MAY_CHOWN);
}