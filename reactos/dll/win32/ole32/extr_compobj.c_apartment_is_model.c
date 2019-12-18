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
struct TYPE_3__ {int multi_threaded; } ;
typedef  int DWORD ;
typedef  int BOOL ;
typedef  TYPE_1__ APARTMENT ;

/* Variables and functions */
 int COINIT_APARTMENTTHREADED ; 

__attribute__((used)) static inline BOOL apartment_is_model(const APARTMENT *apt, DWORD model)
{
    return (apt->multi_threaded == !(model & COINIT_APARTMENTTHREADED));
}