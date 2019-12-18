#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ name; scalar_t__ group; } ;
typedef  TYPE_1__ key_type ;

/* Variables and functions */
 int /*<<< orphan*/  efree (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void inifile_key_free(key_type *key)
{
	if (key->group) {
		efree(key->group);
	}
	if (key->name) {
		efree(key->name);
	}
	memset(key, 0, sizeof(key_type));
}