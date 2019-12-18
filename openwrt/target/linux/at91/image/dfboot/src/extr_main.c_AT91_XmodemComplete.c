#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* Stop ) (TYPE_2__*) ;} ;
struct TYPE_3__ {TYPE_2__ tempo; } ;
typedef  int /*<<< orphan*/  AT91S_PipeStatus ;

/* Variables and functions */
 int XmodemComplete ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 TYPE_1__ svcXmodem ; 

__attribute__((used)) static void AT91_XmodemComplete(AT91S_PipeStatus status, void *pVoid)
{
	/* stop the Xmodem tempo */
	svcXmodem.tempo.Stop(&(svcXmodem.tempo));
	XmodemComplete = 1;
}