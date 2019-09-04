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
struct TYPE_2__ {int /*<<< orphan*/ * field; int /*<<< orphan*/ * count; int /*<<< orphan*/ * el_size; } ;
struct print_arg {TYPE_1__ int_array; int /*<<< orphan*/  type; } ;
struct event_format {int dummy; } ;
typedef  enum event_type { ____Placeholder_event_type } event_type ;

/* Variables and functions */
 int EVENT_ERROR ; 
 int /*<<< orphan*/  PRINT_INT_ARRAY ; 
 scalar_t__ alloc_and_process_delim (struct event_format*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_arg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct print_arg*,int /*<<< orphan*/ ,int) ; 
 int read_token_item (char**) ; 

__attribute__((used)) static enum event_type
process_int_array(struct event_format *event, struct print_arg *arg, char **tok)
{
	memset(arg, 0, sizeof(*arg));
	arg->type = PRINT_INT_ARRAY;

	if (alloc_and_process_delim(event, ",", &arg->int_array.field))
		goto out;

	if (alloc_and_process_delim(event, ",", &arg->int_array.count))
		goto free_field;

	if (alloc_and_process_delim(event, ")", &arg->int_array.el_size))
		goto free_size;

	return read_token_item(tok);

free_size:
	free_arg(arg->int_array.count);
	arg->int_array.count = NULL;
free_field:
	free_arg(arg->int_array.field);
	arg->int_array.field = NULL;
out:
	*tok = NULL;
	return EVENT_ERROR;
}