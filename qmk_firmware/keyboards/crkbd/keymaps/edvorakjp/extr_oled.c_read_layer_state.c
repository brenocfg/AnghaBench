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
typedef  int /*<<< orphan*/  layer_name ;

/* Variables and functions */
#define  L_BASE 130 
#define  _LOWER 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

const char *read_layer_state(void) {
  static char layer_state_str[24];
  char layer_name[17];

  switch (biton32(layer_state)) {
    case L_BASE:
      strcpy(layer_name, "Default");
      break;
    case _RAISE:
      strcpy(layer_name, "Raise");
      break;
    case _LOWER:
      strcpy(layer_name, "Lower");
      break;
    default:
      snprintf(layer_name, sizeof(layer_name), "Undef-%ld", layer_state);
  }

  strcpy(layer_state_str, "Layer: ");

  strcat(layer_state_str, layer_name);
  strcat(layer_state_str, "\n");
  return layer_state_str;
}