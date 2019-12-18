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
typedef  int /*<<< orphan*/  umode_t ;
struct cftype {int flags; scalar_t__ write; scalar_t__ write_s64; scalar_t__ write_u64; scalar_t__ seq_show; scalar_t__ read_s64; scalar_t__ read_u64; } ;

/* Variables and functions */
 int CFTYPE_WORLD_WRITABLE ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  S_IWUGO ; 
 int /*<<< orphan*/  S_IWUSR ; 

__attribute__((used)) static umode_t cgroup_file_mode(const struct cftype *cft)
{
	umode_t mode = 0;

	if (cft->read_u64 || cft->read_s64 || cft->seq_show)
		mode |= S_IRUGO;

	if (cft->write_u64 || cft->write_s64 || cft->write) {
		if (cft->flags & CFTYPE_WORLD_WRITABLE)
			mode |= S_IWUGO;
		else
			mode |= S_IWUSR;
	}

	return mode;
}