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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  StringInfoData ;
typedef  int /*<<< orphan*/  Port ;
typedef  scalar_t__ AuthRequest ;

/* Variables and functions */
 scalar_t__ AUTH_REQ_OK ; 
 scalar_t__ AUTH_REQ_SASL_FIN ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  pq_beginmessage (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_flush () ; 
 int /*<<< orphan*/  pq_sendbytes (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sendAuthRequest(Port *port, AuthRequest areq, const char *extradata, int extralen)
{
	StringInfoData buf;

	CHECK_FOR_INTERRUPTS();

	pq_beginmessage(&buf, 'R');
	pq_sendint32(&buf, (int32) areq);
	if (extralen > 0)
		pq_sendbytes(&buf, extradata, extralen);

	pq_endmessage(&buf);

	/*
	 * Flush message so client will see it, except for AUTH_REQ_OK and
	 * AUTH_REQ_SASL_FIN, which need not be sent until we are ready for
	 * queries.
	 */
	if (areq != AUTH_REQ_OK && areq != AUTH_REQ_SASL_FIN)
		pq_flush();

	CHECK_FOR_INTERRUPTS();
}