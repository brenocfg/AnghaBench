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
struct TYPE_3__ {char* name; scalar_t__* group; } ;
typedef  TYPE_1__ key_type ;

/* Variables and functions */
 char* estrdup (char*) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,scalar_t__*,char*) ; 

char * inifile_key_string(const key_type *key)
{
	if (key->group && *key->group) {
		char *result;
		spprintf(&result, 0, "[%s]%s", key->group, key->name ? key->name : "");
		return result;
	} else if (key->name) {
		return estrdup(key->name);
	} else {
		return NULL;
	}
}