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
struct TYPE_3__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ TLBString ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int memcmp (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int TLB_str_memcmp(void *left, const TLBString *str, DWORD len)
{
    if(!str)
        return 1;
    return memcmp(left, str->str, len);
}