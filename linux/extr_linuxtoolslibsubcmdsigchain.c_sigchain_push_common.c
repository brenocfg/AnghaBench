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
typedef  int /*<<< orphan*/  sigchain_fun ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sigchain_push_common(sigchain_fun f)
{
	sigchain_push(SIGINT, f);
	sigchain_push(SIGHUP, f);
	sigchain_push(SIGTERM, f);
	sigchain_push(SIGQUIT, f);
	sigchain_push(SIGPIPE, f);
}