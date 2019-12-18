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
struct CharacterMatrix {int dummy; } ;

/* Variables and functions */
 scalar_t__ debug_enable ; 
 int /*<<< orphan*/  display ; 
 scalar_t__ is_master ; 
 int /*<<< orphan*/  matrix_clear (struct CharacterMatrix*) ; 
 int /*<<< orphan*/  matrix_update (int /*<<< orphan*/ *,struct CharacterMatrix*) ; 
 int /*<<< orphan*/  render_logo (struct CharacterMatrix*) ; 
 int /*<<< orphan*/  render_status (struct CharacterMatrix*) ; 

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) { return; }
#endif

  matrix_clear(&matrix);
  if (is_master) {
    render_status(&matrix);
  } else {
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}