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
struct v9fs_session_info {int /*<<< orphan*/  cachetag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHETAG_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scnprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int v9fs_random_cachetag(struct v9fs_session_info *v9ses)
{
	v9ses->cachetag = kmalloc(CACHETAG_LEN, GFP_KERNEL);
	if (!v9ses->cachetag)
		return -ENOMEM;

	return scnprintf(v9ses->cachetag, CACHETAG_LEN, "%lu", jiffies);
}