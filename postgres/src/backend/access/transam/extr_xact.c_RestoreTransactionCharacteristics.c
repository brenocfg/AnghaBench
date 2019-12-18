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

/* Variables and functions */
 int /*<<< orphan*/  XactDeferrable ; 
 int /*<<< orphan*/  XactIsoLevel ; 
 int /*<<< orphan*/  XactReadOnly ; 
 int /*<<< orphan*/  save_XactDeferrable ; 
 int /*<<< orphan*/  save_XactIsoLevel ; 
 int /*<<< orphan*/  save_XactReadOnly ; 

void
RestoreTransactionCharacteristics(void)
{
	XactIsoLevel = save_XactIsoLevel;
	XactReadOnly = save_XactReadOnly;
	XactDeferrable = save_XactDeferrable;
}