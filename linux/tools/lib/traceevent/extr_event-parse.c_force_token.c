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
typedef  enum tep_event_type { ____Placeholder_tep_event_type } tep_event_type ;

/* Variables and functions */
 int __read_token (char**) ; 
 int /*<<< orphan*/  init_input_buf (char const*,int /*<<< orphan*/ ) ; 
 char const* input_buf ; 
 unsigned long long input_buf_ptr ; 
 unsigned long long input_buf_siz ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static enum tep_event_type force_token(const char *str, char **tok)
{
	const char *save_input_buf;
	unsigned long long save_input_buf_ptr;
	unsigned long long save_input_buf_siz;
	enum tep_event_type type;
	
	/* save off the current input pointers */
	save_input_buf = input_buf;
	save_input_buf_ptr = input_buf_ptr;
	save_input_buf_siz = input_buf_siz;

	init_input_buf(str, strlen(str));

	type = __read_token(tok);

	/* reset back to original token */
	input_buf = save_input_buf;
	input_buf_ptr = save_input_buf_ptr;
	input_buf_siz = save_input_buf_siz;

	return type;
}