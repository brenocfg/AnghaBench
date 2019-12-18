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
struct TYPE_3__ {int Version; } ;
typedef  TYPE_1__* PMIDL_STUB_DESC ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL is_oicf_stubdesc(const PMIDL_STUB_DESC pStubDesc)
{
    return pStubDesc->Version >= 0x20000;
}