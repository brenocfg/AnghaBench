#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cc; int nbbs; int edges; int ebbs; void* bbsum; } ;
typedef  TYPE_1__ RSignGraph ;

/* Variables and functions */
 void* atoi (char const*) ; 
 scalar_t__ r_str_startswith (char const*,char*) ; 
 char* r_str_word_get0 (char const*,int) ; 

__attribute__((used)) static bool parseGraphMetrics(const char *args0, int nargs, RSignGraph *graph) {
	const char *ptr = NULL;
	int i = 0;

	graph->cc = -1;
	graph->nbbs = -1;
	graph->edges = -1;
	graph->ebbs = -1;
	graph->bbsum = 0;

	for (i = 0; i < nargs; i++) {
		ptr = r_str_word_get0 (args0, i);
		if (r_str_startswith (ptr, "cc=")) {
			graph->cc = atoi (ptr + 3);
		} else if (r_str_startswith (ptr, "nbbs=")) {
			graph->nbbs = atoi (ptr + 5);
		} else if (r_str_startswith (ptr, "edges=")) {
			graph->edges = atoi (ptr + 6);
		} else if (r_str_startswith (ptr, "ebbs=")) {
			graph->ebbs = atoi (ptr + 5);
		} else if (r_str_startswith (ptr, "bbsum=")) {
			graph->bbsum = atoi (ptr + 6);
		} else {
			return false;
		}
	}
	return true;
}