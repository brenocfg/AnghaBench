#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ libgdbr_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int send_ack (TYPE_1__*) ; 
 char* strdup (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strtok (char*,char*) ; 

int handle_qStatus(libgdbr_t *g) {
	if (!g || !g->data || !*g->data) {
		return -1;
	}
	char *data = strdup (g->data);
	char *tok = strtok (data, ";");
	if (!tok) {
		free (data);
		return -1;
	}
	// TODO: We do not yet handle the case where a trace is already running
	if (strncmp (tok, "T0", 2)) {
		send_ack (g);
		free (data);
		return -1;
	}
	// Ensure that trace was never run
	while (tok != NULL) {
		if (!strncmp (tok, "tnotrun:0", 9)) {
			free (data);
			return send_ack (g);
		}
		tok = strtok (NULL, ";");
	}
	send_ack (g);
	free (data);
	return -1;
}