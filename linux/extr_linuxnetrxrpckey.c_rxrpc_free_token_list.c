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
struct rxrpc_key_token {int security_index; int /*<<< orphan*/  k5; struct rxrpc_key_token* kad; struct rxrpc_key_token* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RXRPC_SECURITY_RXK5 129 
#define  RXRPC_SECURITY_RXKAD 128 
 int /*<<< orphan*/  kfree (struct rxrpc_key_token*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rxrpc_rxk5_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_free_token_list(struct rxrpc_key_token *token)
{
	struct rxrpc_key_token *next;

	for (; token; token = next) {
		next = token->next;
		switch (token->security_index) {
		case RXRPC_SECURITY_RXKAD:
			kfree(token->kad);
			break;
		case RXRPC_SECURITY_RXK5:
			if (token->k5)
				rxrpc_rxk5_free(token->k5);
			break;
		default:
			pr_err("Unknown token type %x on rxrpc key\n",
			       token->security_index);
			BUG();
		}

		kfree(token);
	}
}