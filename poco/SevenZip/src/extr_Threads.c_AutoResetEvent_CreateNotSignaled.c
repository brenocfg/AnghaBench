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
typedef  int /*<<< orphan*/  WRes ;
typedef  int /*<<< orphan*/  CAutoResetEvent ;

/* Variables and functions */
 int /*<<< orphan*/  AutoResetEvent_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

WRes AutoResetEvent_CreateNotSignaled(CAutoResetEvent *p) { return AutoResetEvent_Create(p, 0); }