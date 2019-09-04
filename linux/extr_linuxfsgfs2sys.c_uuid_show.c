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
struct super_block {int /*<<< orphan*/  s_uuid; } ;
struct gfs2_sbd {struct super_block* sd_vfs; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ uuid_is_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t uuid_show(struct gfs2_sbd *sdp, char *buf)
{
	struct super_block *s = sdp->sd_vfs;

	buf[0] = '\0';
	if (uuid_is_null(&s->s_uuid))
		return 0;
	return snprintf(buf, PAGE_SIZE, "%pUB\n", &s->s_uuid);
}