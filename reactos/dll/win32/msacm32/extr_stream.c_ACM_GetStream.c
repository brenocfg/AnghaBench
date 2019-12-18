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
typedef  int /*<<< orphan*/  PWINE_ACMSTREAM ;
typedef  int /*<<< orphan*/  HACMSTREAM ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PWINE_ACMSTREAM	ACM_GetStream(HACMSTREAM has)
{
    TRACE("(%p)\n", has);

    return (PWINE_ACMSTREAM)has;
}