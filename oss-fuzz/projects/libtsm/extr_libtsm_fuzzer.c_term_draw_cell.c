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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tsm_age_t ;
struct tsm_screen_attr {int dummy; } ;
struct tsm_screen {int dummy; } ;

/* Variables and functions */
 unsigned int HEIGHT ; 
 unsigned int WIDTH ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static int term_draw_cell(struct tsm_screen *screen, uint32_t id,
                          const uint32_t *ch, size_t len,
                          unsigned int cwidth, unsigned int posx,
                          unsigned int posy,
                          const struct tsm_screen_attr *attr,
                          tsm_age_t age, void *data)
{
  if (posx >= WIDTH || posy >= HEIGHT)
    abort();
  return 0;
}