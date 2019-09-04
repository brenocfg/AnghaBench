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
struct hidp_session {int /*<<< orphan*/  intr_transmit; int /*<<< orphan*/  intr_sock; } ;

/* Variables and functions */
 int hidp_send_message (struct hidp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char,unsigned char const*,int) ; 

__attribute__((used)) static int hidp_send_intr_message(struct hidp_session *session,
				  unsigned char hdr, const unsigned char *data,
				  int size)
{
	return hidp_send_message(session, session->intr_sock,
				 &session->intr_transmit, hdr, data, size);
}