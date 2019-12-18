#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {scalar_t__ gssenc; scalar_t__ ssl_in_use; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  pg_GSS_read (TYPE_1__*,void*,size_t) ; 
 int /*<<< orphan*/  pgtls_read (TYPE_1__*,void*,size_t) ; 
 int /*<<< orphan*/  pqsecure_raw_read (TYPE_1__*,void*,size_t) ; 

ssize_t
pqsecure_read(PGconn *conn, void *ptr, size_t len)
{
	ssize_t		n;

#ifdef USE_SSL
	if (conn->ssl_in_use)
	{
		n = pgtls_read(conn, ptr, len);
	}
	else
#endif
#ifdef ENABLE_GSS
	if (conn->gssenc)
	{
		n = pg_GSS_read(conn, ptr, len);
	}
	else
#endif
	{
		n = pqsecure_raw_read(conn, ptr, len);
	}

	return n;
}