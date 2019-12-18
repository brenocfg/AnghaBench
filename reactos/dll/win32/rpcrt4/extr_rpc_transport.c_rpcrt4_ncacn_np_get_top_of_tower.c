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
struct TYPE_2__ {int count_lhs; size_t count_rhs; int /*<<< orphan*/  protid; } ;
typedef  TYPE_1__ twr_empty_floor_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPM_PROTOCOL_NETBIOS ; 
 int /*<<< orphan*/  EPM_PROTOCOL_SMB ; 
 int /*<<< orphan*/  TRACE (char*,unsigned char*,char const*,char const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static size_t rpcrt4_ncacn_np_get_top_of_tower(unsigned char *tower_data,
                                               const char *networkaddr,
                                               const char *endpoint)
{
    twr_empty_floor_t *smb_floor;
    twr_empty_floor_t *nb_floor;
    size_t size;
    size_t networkaddr_size;
    size_t endpoint_size;

    TRACE("(%p, %s, %s)\n", tower_data, networkaddr, endpoint);

    networkaddr_size = networkaddr ? strlen(networkaddr) + 1 : 1;
    endpoint_size = endpoint ? strlen(endpoint) + 1 : 1;
    size = sizeof(*smb_floor) + endpoint_size + sizeof(*nb_floor) + networkaddr_size;

    if (!tower_data)
        return size;

    smb_floor = (twr_empty_floor_t *)tower_data;

    tower_data += sizeof(*smb_floor);

    smb_floor->count_lhs = sizeof(smb_floor->protid);
    smb_floor->protid = EPM_PROTOCOL_SMB;
    smb_floor->count_rhs = endpoint_size;

    if (endpoint)
        memcpy(tower_data, endpoint, endpoint_size);
    else
        tower_data[0] = 0;
    tower_data += endpoint_size;

    nb_floor = (twr_empty_floor_t *)tower_data;

    tower_data += sizeof(*nb_floor);

    nb_floor->count_lhs = sizeof(nb_floor->protid);
    nb_floor->protid = EPM_PROTOCOL_NETBIOS;
    nb_floor->count_rhs = networkaddr_size;

    if (networkaddr)
        memcpy(tower_data, networkaddr, networkaddr_size);
    else
        tower_data[0] = 0;

    return size;
}