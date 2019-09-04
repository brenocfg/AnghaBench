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
struct TYPE_3__ {char* guid; } ;
typedef  TYPE_1__ PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  config_set_boolean (char*,char*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  registry_free () ; 
 int /*<<< orphan*/  registry_init () ; 
 TYPE_1__* registry_request_access (char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_save () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test1 (int,char**) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv) {
	config_set_boolean("registry", "enabled", 1);

	//debug_flags = 0xFFFFFFFF;
	test1(argc, argv);
	exit(0);

	(void)argc;
	(void)argv;


	PERSON *p1, *p2;

	fprintf(stderr, "\n\nINITIALIZATION\n");

	registry_init();

	int i = 2;

	fprintf(stderr, "\n\nADDING ENTRY\n");
	p1 = registry_request_access("2c95abd0-1542-11e6-8c66-00508db7e9c9", "7c173980-145c-11e6-b86f-00508db7e9c1", "http://localhost:19999/", "test", time(NULL));

	if(0)
	while(i--) {
#ifdef REGISTRY_STDOUT_DUMP
		fprintf(stderr, "\n\nADDING ENTRY\n");
#endif /* REGISTRY_STDOUT_DUMP */
		p1 = registry_request_access(NULL, "7c173980-145c-11e6-b86f-00508db7e9c1", "http://localhost:19999/", "test", time(NULL));

#ifdef REGISTRY_STDOUT_DUMP
		fprintf(stderr, "\n\nADDING ANOTHER URL\n");
#endif /* REGISTRY_STDOUT_DUMP */
		p1 = registry_request_access(p1->guid, "7c173980-145c-11e6-b86f-00508db7e9c1", "http://127.0.0.1:19999/", "test", time(NULL));

#ifdef REGISTRY_STDOUT_DUMP
		fprintf(stderr, "\n\nADDING ANOTHER URL\n");
#endif /* REGISTRY_STDOUT_DUMP */
		p1 = registry_request_access(p1->guid, "7c173980-145c-11e6-b86f-00508db7e9c1", "http://my.server:19999/", "test", time(NULL));

#ifdef REGISTRY_STDOUT_DUMP
		fprintf(stderr, "\n\nADDING ANOTHER MACHINE\n");
#endif /* REGISTRY_STDOUT_DUMP */
		p1 = registry_request_access(p1->guid, "7c173980-145c-11e6-b86f-00508db7e9c1", "http://my.server:19999/", "test", time(NULL));

#ifdef REGISTRY_STDOUT_DUMP
		fprintf(stderr, "\n\nADDING ANOTHER PERSON\n");
#endif /* REGISTRY_STDOUT_DUMP */
		p2 = registry_request_access(NULL, "7c173980-145c-11e6-b86f-00508db7e9c3", "http://localhost:19999/", "test", time(NULL));

#ifdef REGISTRY_STDOUT_DUMP
		fprintf(stderr, "\n\nADDING ANOTHER MACHINE\n");
#endif /* REGISTRY_STDOUT_DUMP */
		p2 = registry_request_access(p2->guid, "7c173980-145c-11e6-b86f-00508db7e9c3", "http://localhost:19999/", "test", time(NULL));
	}

	fprintf(stderr, "\n\nSAVE\n");
	registry_save();

	fprintf(stderr, "\n\nCLEANUP\n");
	registry_free();
	return 0;
}