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
struct TYPE_2__ {int /*<<< orphan*/ * field; int /*<<< orphan*/ * size; } ;
struct print_arg {int type; TYPE_1__ hex; } ;
struct event_format {int dummy; } ;
typedef  enum print_arg_type { ____Placeholder_print_arg_type } print_arg_type ;
typedef  enum event_type { ____Placeholder_event_type } event_type ;

/* Variables and functions */
 int EVENT_ERROR ; 
 scalar_t__ alloc_and_process_delim (struct event_format*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_arg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct print_arg*,int /*<<< orphan*/ ,int) ; 
 int read_token_item (char**) ; 

__attribute__((used)) static enum event_type
process_hex_common(struct event_format *event, struct print_arg *arg,
		   char **tok, enum print_arg_type type)
{
	memset(arg, 0, sizeof(*arg));
	arg->type = type;

	if (alloc_and_process_delim(event, ",", &arg->hex.field))
		goto out;

	if (alloc_and_process_delim(event, ")", &arg->hex.size))
		goto free_field;

	return read_token_item(tok);

free_field:
	free_arg(arg->hex.field);
	arg->hex.field = NULL;
out:
	*tok = NULL;
	return EVENT_ERROR;
}