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
struct subprocess_info {int /*<<< orphan*/  complete; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_usermodehelper_freeinfo (struct subprocess_info*) ; 
 int /*<<< orphan*/  complete (struct completion*) ; 
 struct completion* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void umh_complete(struct subprocess_info *sub_info)
{
	struct completion *comp = xchg(&sub_info->complete, NULL);
	/*
	 * See call_usermodehelper_exec(). If xchg() returns NULL
	 * we own sub_info, the UMH_KILLABLE caller has gone away
	 * or the caller used UMH_NO_WAIT.
	 */
	if (comp)
		complete(comp);
	else
		call_usermodehelper_freeinfo(sub_info);
}