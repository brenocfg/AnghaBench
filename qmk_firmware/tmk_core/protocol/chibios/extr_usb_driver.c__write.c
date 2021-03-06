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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  obqueue; } ;
typedef  TYPE_1__ QMKUSBDriver ;

/* Variables and functions */
 int /*<<< orphan*/  TIME_INFINITE ; 
 size_t obqWriteTimeout (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t _write(void *ip, const uint8_t *bp, size_t n) { return obqWriteTimeout(&((QMKUSBDriver *)ip)->obqueue, bp, n, TIME_INFINITE); }