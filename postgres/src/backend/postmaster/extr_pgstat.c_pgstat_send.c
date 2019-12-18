#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int m_size; } ;
typedef  TYPE_1__ PgStat_MsgHdr ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ pgStatSock ; 
 int send (scalar_t__,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgstat_send(void *msg, int len)
{
	int			rc;

	if (pgStatSock == PGINVALID_SOCKET)
		return;

	((PgStat_MsgHdr *) msg)->m_size = len;

	/* We'll retry after EINTR, but ignore all other failures */
	do
	{
		rc = send(pgStatSock, msg, len, 0);
	} while (rc < 0 && errno == EINTR);

#ifdef USE_ASSERT_CHECKING
	/* In debug builds, log send failures ... */
	if (rc < 0)
		elog(LOG, "could not send to statistics collector: %m");
#endif
}