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
typedef  void mp_dummy_ ;
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void**,void const*,int) ; 

__attribute__((used)) static void *substruct_read_ptr(const void *ptr)
{
    struct mp_dummy_ *res;
    memcpy(&res, ptr, sizeof(res));
    return res;
}