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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  RD_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  iso_connect (char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

RD_BOOL
mcs_connect_start(char *server, char *username, char *domain, char *password,
		  RD_BOOL reconnect, uint32 * selected_protocol)
{
	return iso_connect(server, username, domain, password, reconnect, selected_protocol);
}