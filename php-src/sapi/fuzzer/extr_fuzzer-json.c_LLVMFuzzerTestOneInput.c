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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  php_json_parser ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fuzzer_request_startup () ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  php_json_parser_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,size_t,int,int) ; 
 scalar_t__ php_json_yyparse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_request_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
#ifdef HAVE_JSON
	char *data = malloc(Size+1);
	memcpy(data, Data, Size);
	data[Size] = '\0';

	if (fuzzer_request_startup() == FAILURE) {
		return 0;
	}

	for (int option = 0; option <=1; ++option) {
		zval result;
		php_json_parser parser;
		php_json_parser_init(&parser, &result, data, Size, option, 10);
		if (php_json_yyparse(&parser) == SUCCESS) {
			zval_ptr_dtor(&result);
		}
	}

	php_request_shutdown(NULL);

	free(data);
#else
	fprintf(stderr, "\n\nERROR:\nPHP built without JSON, recompile with --enable-json to use this fuzzer\n");
	exit(1);
#endif
	return 0;
}