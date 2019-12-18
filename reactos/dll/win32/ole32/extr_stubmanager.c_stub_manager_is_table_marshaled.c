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
struct stub_manager {int dummy; } ;
struct ifstub {int flags; } ;
typedef  int /*<<< orphan*/  IPID ;
typedef  int BOOL ;

/* Variables and functions */
 int MSHLFLAGS_TABLESTRONG ; 
 int MSHLFLAGS_TABLEWEAK ; 
 int /*<<< orphan*/  assert (struct ifstub*) ; 
 struct ifstub* stub_manager_ipid_to_ifstub (struct stub_manager*,int /*<<< orphan*/  const*) ; 

BOOL stub_manager_is_table_marshaled(struct stub_manager *m, const IPID *ipid)
{
    struct ifstub *ifstub = stub_manager_ipid_to_ifstub(m, ipid);
 
    assert( ifstub );
    
    return ifstub->flags & (MSHLFLAGS_TABLESTRONG | MSHLFLAGS_TABLEWEAK);
}