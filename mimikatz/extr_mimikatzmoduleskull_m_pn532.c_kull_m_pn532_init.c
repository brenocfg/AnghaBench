#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  descr; int /*<<< orphan*/  suppdata; int /*<<< orphan*/  communicator; } ;
typedef  int /*<<< orphan*/  PKULL_M_PN532_COMM_CALLBACK ;
typedef  TYPE_1__* PKULL_M_PN532_COMM ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */

void kull_m_pn532_init(PKULL_M_PN532_COMM_CALLBACK communicator, LPVOID suppdata, BOOL descr, PKULL_M_PN532_COMM comm)
{
	comm->communicator = communicator;
	comm->suppdata = suppdata;
	comm->descr = descr;
}