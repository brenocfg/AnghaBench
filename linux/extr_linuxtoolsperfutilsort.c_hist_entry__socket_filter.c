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
struct hist_entry {int socket; } ;

/* Variables and functions */
 int HIST_FILTER__SOCKET ; 

__attribute__((used)) static int hist_entry__socket_filter(struct hist_entry *he, int type, const void *arg)
{
	int sk = *(const int *)arg;

	if (type != HIST_FILTER__SOCKET)
		return -1;

	return sk >= 0 && he->socket != sk;
}