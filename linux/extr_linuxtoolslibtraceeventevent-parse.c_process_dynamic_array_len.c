#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ index; struct format_field* field; } ;
struct print_arg {TYPE_1__ dynarray; int /*<<< orphan*/  type; } ;
struct format_field {int dummy; } ;
struct event_format {int dummy; } ;
typedef  enum event_type { ____Placeholder_event_type } event_type ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DELIM ; 
 int EVENT_ERROR ; 
 int /*<<< orphan*/  EVENT_ITEM ; 
 int /*<<< orphan*/  PRINT_DYNAMIC_ARRAY_LEN ; 
 int /*<<< orphan*/  free_token (char*) ; 
 scalar_t__ read_expect_type (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ read_expected (int /*<<< orphan*/ ,char*) ; 
 int read_token (char**) ; 
 struct format_field* tep_find_field (struct event_format*,char*) ; 

__attribute__((used)) static enum event_type
process_dynamic_array_len(struct event_format *event, struct print_arg *arg,
			  char **tok)
{
	struct format_field *field;
	enum event_type type;
	char *token;

	if (read_expect_type(EVENT_ITEM, &token) < 0)
		goto out_free;

	arg->type = PRINT_DYNAMIC_ARRAY_LEN;

	/* Find the field */
	field = tep_find_field(event, token);
	if (!field)
		goto out_free;

	arg->dynarray.field = field;
	arg->dynarray.index = 0;

	if (read_expected(EVENT_DELIM, ")") < 0)
		goto out_err;

	type = read_token(&token);
	*tok = token;

	return type;

 out_free:
	free_token(token);
 out_err:
	*tok = NULL;
	return EVENT_ERROR;
}