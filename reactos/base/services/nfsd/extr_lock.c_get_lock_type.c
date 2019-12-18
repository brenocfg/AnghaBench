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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  READW_LT ; 
 int /*<<< orphan*/  READ_LT ; 
 int /*<<< orphan*/  WRITEW_LT ; 
 int /*<<< orphan*/  WRITE_LT ; 

__attribute__((used)) static __inline uint32_t get_lock_type(BOOLEAN exclusive, BOOLEAN blocking)
{
    return blocking == 0
        ? ( exclusive == 0 ? READ_LT : WRITE_LT )
        : ( exclusive == 0 ? READW_LT : WRITEW_LT );
}