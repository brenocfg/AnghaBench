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
struct TYPE_3__ {char const* name; } ;
typedef  TYPE_1__ RKext ;

/* Variables and functions */
 char* strrchr (char const*,char) ; 

__attribute__((used)) static const char *kext_short_name(RKext *kext) {
	const char *sn = strrchr (kext->name, '.');
	return sn ? sn + 1 : kext->name;
}