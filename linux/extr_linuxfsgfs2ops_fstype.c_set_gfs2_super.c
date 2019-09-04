#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* s_bdev; int /*<<< orphan*/  s_bdi; int /*<<< orphan*/  s_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_bdi; int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdi_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_gfs2_super(struct super_block *s, void *data)
{
	s->s_bdev = data;
	s->s_dev = s->s_bdev->bd_dev;
	s->s_bdi = bdi_get(s->s_bdev->bd_bdi);
	return 0;
}