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
struct sock {int /*<<< orphan*/ * sk_data_ready; } ;
struct sk_psock_parser {int enabled; int /*<<< orphan*/  strp; int /*<<< orphan*/ * saved_data_ready; } ;
struct sk_psock {struct sk_psock_parser parser; } ;

/* Variables and functions */
 int /*<<< orphan*/  strp_stop (int /*<<< orphan*/ *) ; 

void sk_psock_stop_strp(struct sock *sk, struct sk_psock *psock)
{
	struct sk_psock_parser *parser = &psock->parser;

	if (!parser->enabled)
		return;

	sk->sk_data_ready = parser->saved_data_ready;
	parser->saved_data_ready = NULL;
	strp_stop(&parser->strp);
	parser->enabled = false;
}