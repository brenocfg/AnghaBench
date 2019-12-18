#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RBinSection ;

/* Variables and functions */
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool __isDataSection(RBinSection *sect) {
	if (strstr (sect->name, "_cstring")) {
		return true;
	}
	if (strstr (sect->name, "_objc_methname")) {
		return true;
	}
	if (strstr (sect->name, "_objc_classname")) {
		return true;
	}
	if (strstr (sect->name, "_objc_methtype")) {
		return true;
	}
	return false;
}