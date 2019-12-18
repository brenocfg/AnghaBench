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
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  PgBackendStatus ;
typedef  int /*<<< orphan*/  PgBackendSSLStatus ;

/* Variables and functions */
 int NAMEDATALEN ; 
 int /*<<< orphan*/  NumBackendStatSlots ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_size (int,int /*<<< orphan*/ ) ; 
 int pgstat_track_activity_query_size ; 

Size
BackendStatusShmemSize(void)
{
	Size		size;

	/* BackendStatusArray: */
	size = mul_size(sizeof(PgBackendStatus), NumBackendStatSlots);
	/* BackendAppnameBuffer: */
	size = add_size(size,
					mul_size(NAMEDATALEN, NumBackendStatSlots));
	/* BackendClientHostnameBuffer: */
	size = add_size(size,
					mul_size(NAMEDATALEN, NumBackendStatSlots));
	/* BackendActivityBuffer: */
	size = add_size(size,
					mul_size(pgstat_track_activity_query_size, NumBackendStatSlots));
#ifdef USE_SSL
	/* BackendSslStatusBuffer: */
	size = add_size(size,
					mul_size(sizeof(PgBackendSSLStatus), NumBackendStatSlots));
#endif
	return size;
}