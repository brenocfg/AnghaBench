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
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ RCFValueString ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* r_str_replace (char*,char*,char*,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_cf_value_string_print(RCFValueString *string) {
	char *escaped = strdup (string->value);
	escaped = r_str_replace (escaped, "\"", "\\\"", 1);
	printf ("\"%s\"", escaped);
	R_FREE (escaped);
}