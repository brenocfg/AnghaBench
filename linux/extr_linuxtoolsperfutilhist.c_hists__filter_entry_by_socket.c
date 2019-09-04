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
struct hists {int socket_filter; } ;
struct hist_entry {int socket; int filtered; } ;

/* Variables and functions */
 int HIST_FILTER__SOCKET ; 

__attribute__((used)) static bool hists__filter_entry_by_socket(struct hists *hists,
					  struct hist_entry *he)
{
	if ((hists->socket_filter > -1) &&
	    (he->socket != hists->socket_filter)) {
		he->filtered |= (1 << HIST_FILTER__SOCKET);
		return true;
	}

	return false;
}