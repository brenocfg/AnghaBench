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
struct evsel {int dummy; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 struct evsel* evlist__last (struct evlist*) ; 
 int evsel__enable (struct evsel*) ; 

__attribute__((used)) static int detach__disable(struct evlist *evlist)
{
	struct evsel *evsel = evlist__last(evlist);

	return evsel__enable(evsel);
}