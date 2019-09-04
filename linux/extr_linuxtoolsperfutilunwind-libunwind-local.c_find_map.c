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
typedef  int /*<<< orphan*/  unw_word_t ;
struct unwind_info {int /*<<< orphan*/  thread; } ;
struct map {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 struct map* thread__find_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addr_location*) ; 

__attribute__((used)) static struct map *find_map(unw_word_t ip, struct unwind_info *ui)
{
	struct addr_location al;
	return thread__find_map(ui->thread, PERF_RECORD_MISC_USER, ip, &al);
}