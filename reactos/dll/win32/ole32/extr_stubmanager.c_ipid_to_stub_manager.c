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
struct ifstub {int dummy; } ;
typedef  int /*<<< orphan*/  IPID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  APARTMENT ;

/* Variables and functions */
 int /*<<< orphan*/  ipid_to_ifstub (int /*<<< orphan*/  const*,int /*<<< orphan*/ **,struct stub_manager**,struct ifstub**) ; 

__attribute__((used)) static HRESULT ipid_to_stub_manager(const IPID *ipid, APARTMENT **stub_apt, struct stub_manager **stub)
{
    struct ifstub *ifstub;
    return ipid_to_ifstub(ipid, stub_apt, stub, &ifstub);
}