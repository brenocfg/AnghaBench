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
typedef  int /*<<< orphan*/  uint8_t ;
struct tsm_vte {int dummy; } ;
struct tsm_screen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIGHT ; 
 int /*<<< orphan*/  WIDTH ; 
 int /*<<< orphan*/  term_draw_cell ; 
 int /*<<< orphan*/  terminal_write_fn ; 
 int /*<<< orphan*/  tsm_screen_draw (struct tsm_screen*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsm_screen_new (struct tsm_screen**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsm_screen_resize (struct tsm_screen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsm_screen_set_max_sb (struct tsm_screen*,int const) ; 
 int /*<<< orphan*/  tsm_screen_unref (struct tsm_screen*) ; 
 int /*<<< orphan*/  tsm_vte_input (struct tsm_vte*,char const*,size_t) ; 
 int /*<<< orphan*/  tsm_vte_new (struct tsm_vte**,struct tsm_screen*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsm_vte_unref (struct tsm_vte*) ; 

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct tsm_screen *screen;
  struct tsm_vte *vte;
  const int scrollback_size = 200;  // frecon use 200

  tsm_screen_new(&screen, NULL, NULL);
  tsm_screen_set_max_sb(screen, scrollback_size);
  tsm_vte_new(&vte, screen, terminal_write_fn, NULL, NULL, NULL);
  tsm_screen_resize(screen, WIDTH, HEIGHT);

  tsm_vte_input(vte, (const char*) data, size);
  tsm_screen_draw(screen, term_draw_cell, NULL);

  tsm_vte_unref(vte);
  tsm_screen_unref(screen);
  return 0;
}