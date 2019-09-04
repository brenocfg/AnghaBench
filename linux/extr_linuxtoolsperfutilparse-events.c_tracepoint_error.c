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
struct parse_events_error {void* help; void* str; } ;
typedef  int /*<<< orphan*/  help ;

/* Variables and functions */
 int BUFSIZ ; 
#define  EACCES 129 
#define  ENOENT 128 
 int abs (int) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  tracing_path__strerror_open_tp (int,char*,int,char const*,char const*) ; 

__attribute__((used)) static void tracepoint_error(struct parse_events_error *e, int err,
			     const char *sys, const char *name)
{
	char help[BUFSIZ];

	if (!e)
		return;

	/*
	 * We get error directly from syscall errno ( > 0),
	 * or from encoded pointer's error ( < 0).
	 */
	err = abs(err);

	switch (err) {
	case EACCES:
		e->str = strdup("can't access trace events");
		break;
	case ENOENT:
		e->str = strdup("unknown tracepoint");
		break;
	default:
		e->str = strdup("failed to add tracepoint");
		break;
	}

	tracing_path__strerror_open_tp(err, help, sizeof(help), sys, name);
	e->help = strdup(help);
}