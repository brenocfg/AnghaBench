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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  LlbSerialPutChar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LlbVideoPutChar (int /*<<< orphan*/ ) ; 

VOID
LlbFwPutChar(INT Ch)
{
    /* Just call directly the video function */
    LlbVideoPutChar(Ch);

    /* DEBUG ONLY */
    LlbSerialPutChar(Ch);
}