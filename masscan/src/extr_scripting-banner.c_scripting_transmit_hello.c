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
typedef  struct InteractiveData const InteractiveData ;
typedef  struct InteractiveData Banner1 ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UNUSEDPARM (struct InteractiveData const*) ; 

__attribute__((used)) static void
scripting_transmit_hello(const struct Banner1 *banner1, struct InteractiveData *more)
{
    UNUSEDPARM(banner1); UNUSEDPARM(more);
    LOG(0, "SCRIPTING: HELLO\n");
}