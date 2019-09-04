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
struct TYPE_3__ {int is_metric; int is_metric_timeout; } ;
typedef  TYPE_1__ UIState ;

/* Variables and functions */
 int UI_FREQ ; 
 int /*<<< orphan*/  free (char*) ; 
 int read_db_value (int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_is_metric(UIState *s) {
  char *is_metric;
  const int result = read_db_value(NULL, "IsMetric", &is_metric, NULL);
  if (result == 0) {
    s->is_metric = is_metric[0] == '1';
    free(is_metric);
  }
  s->is_metric_timeout = 2 * UI_FREQ; // 0.5Hz
}