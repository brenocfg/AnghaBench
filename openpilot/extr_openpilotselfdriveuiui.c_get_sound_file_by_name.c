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
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ sound_file ;

/* Variables and functions */
 TYPE_1__* sound_table ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

sound_file* get_sound_file_by_name(const char* name) {
  for (sound_file *s = sound_table; s->name != NULL; s++) {
    if (strcmp(s->name, name) == 0) {
      return s;
    }
  }

  return NULL;
}