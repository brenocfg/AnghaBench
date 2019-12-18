#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ptype; } ;
struct TYPE_5__ {TYPE_1__ common; } ;
typedef  TYPE_2__ RpcPktHdr ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ PKT_BIND_NACK ; 
 scalar_t__ PKT_SHUTDOWN ; 

__attribute__((used)) static BOOL packet_has_auth_verifier(const RpcPktHdr *Header)
{
    return !(Header->common.ptype == PKT_BIND_NACK) &&
           !(Header->common.ptype == PKT_SHUTDOWN);
}