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
typedef  int uint16_t ;

/* Variables and functions */
 char*** cfq_word_lut ; 
 char* cfq_word_lut_title_caps ; 

void matrix_init_user(void) {

  /* Duplicate 'cfq_word_lut[0][...]' into 'cfq_word_lut[1][...]' */
  {
    char *d = cfq_word_lut_title_caps;
    for (uint16_t i = 0; i < 26; i++) {
      char *s = cfq_word_lut[0][i];
      cfq_word_lut[1][i] = d;
      while ((*d++ = *s++)) {}
    }
  }
  /* Title caps. */
  for (uint16_t i = 0; i < 26; i++) {
    char *w = cfq_word_lut[1][i];
    bool prev_is_alpha = false;
    if (*w) {
      while (*w) {
        bool is_lower = (*w >= 'a' && *w <= 'z');
        bool is_upper = (*w >= 'A' && *w <= 'Z');
        if (prev_is_alpha == false && is_lower) {
          *w -= ('a' - 'A');
        }
        prev_is_alpha = is_lower || is_upper;
        w++;
      }
    }
  }
}