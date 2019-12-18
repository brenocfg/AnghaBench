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
struct tls_rec {int /*<<< orphan*/  msg_plaintext; int /*<<< orphan*/  msg_encrypted; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tls_rec*) ; 
 int /*<<< orphan*/  sk_msg_free (struct sock*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tls_free_rec(struct sock *sk, struct tls_rec *rec)
{
	sk_msg_free(sk, &rec->msg_encrypted);
	sk_msg_free(sk, &rec->msg_plaintext);
	kfree(rec);
}