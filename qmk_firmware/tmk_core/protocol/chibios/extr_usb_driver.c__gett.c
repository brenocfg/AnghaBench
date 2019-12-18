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
typedef  int /*<<< orphan*/  systime_t ;
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_2__ {int /*<<< orphan*/  ibqueue; } ;
typedef  TYPE_1__ QMKUSBDriver ;

/* Variables and functions */
 int /*<<< orphan*/  ibqGetTimeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static msg_t _gett(void *ip, systime_t timeout) { return ibqGetTimeout(&((QMKUSBDriver *)ip)->ibqueue, timeout); }