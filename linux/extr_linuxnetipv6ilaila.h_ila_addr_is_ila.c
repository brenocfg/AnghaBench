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
struct TYPE_2__ {scalar_t__ type; } ;
struct ila_addr {TYPE_1__ ident; } ;

/* Variables and functions */
 scalar_t__ ILA_ATYPE_IID ; 

__attribute__((used)) static inline bool ila_addr_is_ila(struct ila_addr *iaddr)
{
	return (iaddr->ident.type != ILA_ATYPE_IID);
}