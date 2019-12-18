#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* parsed_as; int error; int /*<<< orphan*/  error_msg; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ EVAL_EXPRESSION ;

/* Variables and functions */
 char* buffer_tostring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ expression_evaluate (TYPE_1__*) ; 
 int /*<<< orphan*/  expression_free (TYPE_1__*) ; 
 TYPE_1__* expression_parse (char*,char const**,int*) ; 
 char* expression_strerror (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv) {
	if(argc != 2) {
		fprintf(stderr, "I need an epxression (enclose it in single-quotes (') as a single parameter)\n");
		exit(1);
	}

	const char *failed_at = NULL;
	int error;

	EVAL_EXPRESSION *exp = expression_parse(argv[1], &failed_at, &error);
	if(!exp)
		printf("\nPARSING FAILED\nExpression: '%s'\nParsing stopped at: '%s'\nParsing error code: %d (%s)\n", argv[1], (failed_at)?((*failed_at)?failed_at:"<END OF EXPRESSION>"):"<NONE>", error, expression_strerror(error));
	
	else {
		printf("\nPARSING OK\nExpression: '%s'\nParsed as : '%s'\nParsing error code: %d (%s)\n", argv[1], exp->parsed_as, error, expression_strerror(error));

		if(expression_evaluate(exp)) {
			printf("\nEvaluates to: %Lf\n\n", exp->result);
		}
		else {
			printf("\nEvaluation failed with code %d and message: %s\n\n", exp->error, buffer_tostring(exp->error_msg));
		}
		expression_free(exp);
	}

	return 0;
}