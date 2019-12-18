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
struct tep_print_arg {int dummy; } ;
struct tep_event {int dummy; } ;
typedef  enum tep_event_type { ____Placeholder_tep_event_type } tep_event_type ;

/* Variables and functions */
 int process_arg_token (struct tep_event*,struct tep_print_arg*,char**,int) ; 
 int read_token (char**) ; 

__attribute__((used)) static enum tep_event_type
process_arg(struct tep_event *event, struct tep_print_arg *arg, char **tok)
{
	enum tep_event_type type;
	char *token;

	type = read_token(&token);
	*tok = token;

	return process_arg_token(event, arg, tok, type);
}