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
typedef  int /*<<< orphan*/  PQEnvironmentOption ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int build_startup_packet (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 
 scalar_t__ malloc (int) ; 

char *
pqBuildStartupPacket3(PGconn *conn, int *packetlen,
					  const PQEnvironmentOption *options)
{
	char	   *startpacket;

	*packetlen = build_startup_packet(conn, NULL, options);
	startpacket = (char *) malloc(*packetlen);
	if (!startpacket)
		return NULL;
	*packetlen = build_startup_packet(conn, startpacket, options);
	return startpacket;
}