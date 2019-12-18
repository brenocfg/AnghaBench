#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* flag; char* desc; } ;
struct TYPE_5__ {char* name; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 TYPE_3__* args ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 TYPE_2__* proc ; 
 TYPE_1__** procs ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static void spp_help(char *argv0) {
	int i;
	char supported[128] = "";
	for( i = 0; procs[i]; ++i ) {
		if (i) strcat (supported, ",");
		strcat (supported, procs[i]->name);
	}
	printf("Usage: %s [-othesv] [file] [...]\n", argv0);
	printf(	"  -o [file]     set output file (stdout)\n"
		"  -t [type]     define processor type (%s)\n"
		"  -e [str]      evaluate this string with the selected proc\n"
		"  -s [str]      show this string before anything\n"
		"  -l            list all built-in preprocessors\n"
		"  -L            list keywords registered by the processor\n"
		"  -n            do not read from stdin\n"
		"  -v            show version information\n", supported);
	if (proc) {
		printf ("%s specific flags:\n", proc->name);
		for(i = 0; args[i].flag; i++) {
			printf (" %s   %s\n", args[i].flag, args[i].desc);
		}
	}
	exit(0);
}