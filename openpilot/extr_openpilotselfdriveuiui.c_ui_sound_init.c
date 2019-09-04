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
struct TYPE_3__ {int /*<<< orphan*/  uri; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ sound_file ;

/* Variables and functions */
 int /*<<< orphan*/  slplay_create_player_for_uri (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  slplay_setup (char**) ; 
 TYPE_1__* sound_table ; 

void ui_sound_init(char **error) {
  slplay_setup(error);
  if (*error) return;

  for (sound_file *s = sound_table; s->name != NULL; s++) {
    slplay_create_player_for_uri(s->uri, error);
    if (*error) return;
  }
}