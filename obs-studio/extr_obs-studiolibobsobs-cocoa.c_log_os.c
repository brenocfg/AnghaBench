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
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  SEL ;
typedef  scalar_t__ Class ;

/* Variables and functions */
 int /*<<< orphan*/  log_os_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_os_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ objc_getClass (char*) ; 
 int /*<<< orphan*/  objc_msgSend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sel_registerName (char*) ; 

__attribute__((used)) static void log_os(void)
{
	Class NSProcessInfo = objc_getClass("NSProcessInfo");
	id pi  = objc_msgSend((id)NSProcessInfo,
			sel_registerName("processInfo"));

	SEL UTF8String = sel_registerName("UTF8String");

	log_os_name(pi, UTF8String);
	log_os_version(pi, UTF8String);
}