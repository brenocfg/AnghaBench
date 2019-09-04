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
struct diff_hpp_fmt {int /*<<< orphan*/  header; } ;
struct data__file {struct diff_hpp_fmt* fmt; } ;

/* Variables and functions */
 int PERF_HPP_DIFF__MAX_INDEX ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void data__free(struct data__file *d)
{
	int col;

	for (col = 0; col < PERF_HPP_DIFF__MAX_INDEX; col++) {
		struct diff_hpp_fmt *fmt = &d->fmt[col];

		zfree(&fmt->header);
	}
}