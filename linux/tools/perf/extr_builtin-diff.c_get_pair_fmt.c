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
struct hist_entry {int dummy; } ;
struct diff_hpp_fmt {int /*<<< orphan*/  fmt; } ;
struct data__file {int dummy; } ;

/* Variables and functions */
 struct data__file* fmt_to_data_file (int /*<<< orphan*/ *) ; 
 struct hist_entry* get_pair_data (struct hist_entry*,struct data__file*) ; 

__attribute__((used)) static struct hist_entry*
get_pair_fmt(struct hist_entry *he, struct diff_hpp_fmt *dfmt)
{
	struct data__file *d = fmt_to_data_file(&dfmt->fmt);

	return get_pair_data(he, d);
}