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
struct x25_sock {int state; int condition; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  X25_CLEAR_REQUEST ; 
 int X25_COND_ACK_PENDING ; 
#define  X25_STATE_1 131 
#define  X25_STATE_2 130 
#define  X25_STATE_3 129 
#define  X25_STATE_4 128 
 int /*<<< orphan*/  x25_disconnect (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x25_enquiry_response (struct sock*) ; 
 struct x25_sock* x25_sk (struct sock*) ; 
 int /*<<< orphan*/  x25_start_t23timer (struct sock*) ; 
 int /*<<< orphan*/  x25_write_internal (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void x25_do_timer_expiry(struct sock * sk)
{
	struct x25_sock *x25 = x25_sk(sk);

	switch (x25->state) {

		case X25_STATE_3:	/* T2 */
			if (x25->condition & X25_COND_ACK_PENDING) {
				x25->condition &= ~X25_COND_ACK_PENDING;
				x25_enquiry_response(sk);
			}
			break;

		case X25_STATE_1:	/* T21 */
		case X25_STATE_4:	/* T22 */
			x25_write_internal(sk, X25_CLEAR_REQUEST);
			x25->state = X25_STATE_2;
			x25_start_t23timer(sk);
			break;

		case X25_STATE_2:	/* T23 */
			x25_disconnect(sk, ETIMEDOUT, 0, 0);
			break;
	}
}