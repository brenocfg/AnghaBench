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
struct hists {int socket_filter; scalar_t__ symbol_filter_str; scalar_t__ dso_filter; scalar_t__ thread_filter; } ;

/* Variables and functions */

__attribute__((used)) static inline bool hists__has_filter(struct hists *hists)
{
	return hists->thread_filter || hists->dso_filter ||
		hists->symbol_filter_str || (hists->socket_filter > -1);
}