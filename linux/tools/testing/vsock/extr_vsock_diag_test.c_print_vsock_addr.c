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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int VMADDR_CID_ANY ; 
 unsigned int VMADDR_PORT_ANY ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void print_vsock_addr(FILE *fp, unsigned int cid, unsigned int port)
{
	if (cid == VMADDR_CID_ANY)
		fprintf(fp, "*:");
	else
		fprintf(fp, "%u:", cid);

	if (port == VMADDR_PORT_ANY)
		fprintf(fp, "*");
	else
		fprintf(fp, "%u", port);
}