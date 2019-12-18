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
typedef  int /*<<< orphan*/  timeout_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMEOUT_MAX ; 
 int WHEEL_BIT ; 
 int fls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int timeout_wheel(timeout_t timeout)
{
    /* must be called with timeout != 0, so fls input is nonzero */
    return (fls(MIN(timeout, TIMEOUT_MAX)) - 1) / WHEEL_BIT;
}