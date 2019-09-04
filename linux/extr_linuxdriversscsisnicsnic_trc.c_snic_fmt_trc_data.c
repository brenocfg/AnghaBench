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
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct snic_trc_data {int /*<<< orphan*/ * data; int /*<<< orphan*/  tag; int /*<<< orphan*/  hno; int /*<<< orphan*/  fn; int /*<<< orphan*/  ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies_to_timespec64 (int /*<<< orphan*/ ,struct timespec64*) ; 
 scalar_t__ snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snic_fmt_trc_data(struct snic_trc_data *td, char *buf, int buf_sz)
{
	int len = 0;
	struct timespec64 tmspec;

	jiffies_to_timespec64(td->ts, &tmspec);

	len += snprintf(buf, buf_sz,
			"%llu.%09lu %-25s %3d %4x %16llx %16llx %16llx %16llx %16llx\n",
			tmspec.tv_sec,
			tmspec.tv_nsec,
			td->fn,
			td->hno,
			td->tag,
			td->data[0], td->data[1], td->data[2], td->data[3],
			td->data[4]);

	return len;
}