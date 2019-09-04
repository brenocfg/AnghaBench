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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_RECORD_TYPE_DATA ; 
 int tls_push_record (struct sock*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tls_sw_push_pending_record(struct sock *sk, int flags)
{
	return tls_push_record(sk, flags, TLS_RECORD_TYPE_DATA);
}