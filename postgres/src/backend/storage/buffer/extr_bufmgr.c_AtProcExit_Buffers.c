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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AbortBufferIO () ; 
 int /*<<< orphan*/  AtProcExit_LocalBuffers () ; 
 int /*<<< orphan*/  CheckForBufferLeaks () ; 
 int /*<<< orphan*/  UnlockBuffers () ; 

__attribute__((used)) static void
AtProcExit_Buffers(int code, Datum arg)
{
	AbortBufferIO();
	UnlockBuffers();

	CheckForBufferLeaks();

	/* localbuf.c needs a chance too */
	AtProcExit_LocalBuffers();
}