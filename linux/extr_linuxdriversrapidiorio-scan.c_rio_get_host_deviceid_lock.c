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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rio_mport {int /*<<< orphan*/  sys_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_ANY_DESTID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RIO_HOST_DID_LOCK_CSR ; 
 int /*<<< orphan*/  rio_mport_read_config_32 (struct rio_mport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u16 rio_get_host_deviceid_lock(struct rio_mport *port, u8 hopcount)
{
	u32 result;

	rio_mport_read_config_32(port, RIO_ANY_DESTID(port->sys_size), hopcount,
				 RIO_HOST_DID_LOCK_CSR, &result);

	return (u16) (result & 0xffff);
}