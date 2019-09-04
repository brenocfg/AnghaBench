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
struct sample_t {int* values; int min; int max; } ;

/* Variables and functions */

void update_sample(struct sample_t *sample, int sample_new) {
  for (int i = sizeof(sample->values)/sizeof(sample->values[0]) - 1; i > 0; i--) {
    sample->values[i] = sample->values[i-1];
  }
  sample->values[0] = sample_new;

  // get the minimum and maximum measured samples
  sample->min = sample->max = sample->values[0];
  for (int i = 1; i < sizeof(sample->values)/sizeof(sample->values[0]); i++) {
    if (sample->values[i] < sample->min) sample->min = sample->values[i];
    if (sample->values[i] > sample->max) sample->max = sample->values[i];
  }
}