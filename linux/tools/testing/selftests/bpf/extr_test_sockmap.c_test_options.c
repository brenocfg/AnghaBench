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

/* Variables and functions */
 int OPTSTRING ; 
 scalar_t__ ktls ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ peek_flag ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 
 int txmsg_apply ; 
 int txmsg_cork ; 
 scalar_t__ txmsg_drop ; 
 int txmsg_end ; 
 scalar_t__ txmsg_ingress ; 
 scalar_t__ txmsg_noisy ; 
 scalar_t__ txmsg_pass ; 
 int txmsg_pop ; 
 scalar_t__ txmsg_redir ; 
 scalar_t__ txmsg_redir_noisy ; 
 scalar_t__ txmsg_skb ; 
 int txmsg_start ; 
 int txmsg_start_pop ; 

__attribute__((used)) static void test_options(char *options)
{
	char tstr[OPTSTRING];

	memset(options, 0, OPTSTRING);

	if (txmsg_pass)
		strncat(options, "pass,", OPTSTRING);
	if (txmsg_noisy)
		strncat(options, "pass_noisy,", OPTSTRING);
	if (txmsg_redir)
		strncat(options, "redir,", OPTSTRING);
	if (txmsg_redir_noisy)
		strncat(options, "redir_noisy,", OPTSTRING);
	if (txmsg_drop)
		strncat(options, "drop,", OPTSTRING);
	if (txmsg_apply) {
		snprintf(tstr, OPTSTRING, "apply %d,", txmsg_apply);
		strncat(options, tstr, OPTSTRING);
	}
	if (txmsg_cork) {
		snprintf(tstr, OPTSTRING, "cork %d,", txmsg_cork);
		strncat(options, tstr, OPTSTRING);
	}
	if (txmsg_start) {
		snprintf(tstr, OPTSTRING, "start %d,", txmsg_start);
		strncat(options, tstr, OPTSTRING);
	}
	if (txmsg_end) {
		snprintf(tstr, OPTSTRING, "end %d,", txmsg_end);
		strncat(options, tstr, OPTSTRING);
	}
	if (txmsg_start_pop) {
		snprintf(tstr, OPTSTRING, "pop (%d,%d),",
			 txmsg_start_pop, txmsg_start_pop + txmsg_pop);
		strncat(options, tstr, OPTSTRING);
	}
	if (txmsg_ingress)
		strncat(options, "ingress,", OPTSTRING);
	if (txmsg_skb)
		strncat(options, "skb,", OPTSTRING);
	if (ktls)
		strncat(options, "ktls,", OPTSTRING);
	if (peek_flag)
		strncat(options, "peek,", OPTSTRING);
}