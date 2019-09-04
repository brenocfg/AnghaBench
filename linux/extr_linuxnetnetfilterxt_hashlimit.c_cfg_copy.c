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
struct hashlimit_cfg3 {int /*<<< orphan*/  dstmask; int /*<<< orphan*/  srcmask; int /*<<< orphan*/  expire; int /*<<< orphan*/  gc_interval; int /*<<< orphan*/  max; int /*<<< orphan*/  size; int /*<<< orphan*/  burst; int /*<<< orphan*/  avg; int /*<<< orphan*/  mode; } ;
struct hashlimit_cfg2 {int /*<<< orphan*/  dstmask; int /*<<< orphan*/  srcmask; int /*<<< orphan*/  expire; int /*<<< orphan*/  gc_interval; int /*<<< orphan*/  max; int /*<<< orphan*/  size; int /*<<< orphan*/  burst; int /*<<< orphan*/  avg; int /*<<< orphan*/  mode; } ;
struct hashlimit_cfg1 {int /*<<< orphan*/  dstmask; int /*<<< orphan*/  srcmask; int /*<<< orphan*/  expire; int /*<<< orphan*/  gc_interval; int /*<<< orphan*/  max; int /*<<< orphan*/  size; int /*<<< orphan*/  burst; int /*<<< orphan*/  avg; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (struct hashlimit_cfg3*,void const*,int) ; 

__attribute__((used)) static int
cfg_copy(struct hashlimit_cfg3 *to, const void *from, int revision)
{
	if (revision == 1) {
		struct hashlimit_cfg1 *cfg = (struct hashlimit_cfg1 *)from;

		to->mode = cfg->mode;
		to->avg = cfg->avg;
		to->burst = cfg->burst;
		to->size = cfg->size;
		to->max = cfg->max;
		to->gc_interval = cfg->gc_interval;
		to->expire = cfg->expire;
		to->srcmask = cfg->srcmask;
		to->dstmask = cfg->dstmask;
	} else if (revision == 2) {
		struct hashlimit_cfg2 *cfg = (struct hashlimit_cfg2 *)from;

		to->mode = cfg->mode;
		to->avg = cfg->avg;
		to->burst = cfg->burst;
		to->size = cfg->size;
		to->max = cfg->max;
		to->gc_interval = cfg->gc_interval;
		to->expire = cfg->expire;
		to->srcmask = cfg->srcmask;
		to->dstmask = cfg->dstmask;
	} else if (revision == 3) {
		memcpy(to, from, sizeof(struct hashlimit_cfg3));
	} else {
		return -EINVAL;
	}

	return 0;
}