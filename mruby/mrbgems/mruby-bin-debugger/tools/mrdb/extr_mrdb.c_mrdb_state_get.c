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
typedef  int /*<<< orphan*/  mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/ * _mrdb_state ; 
 int /*<<< orphan*/ * mrdb_state_new (int /*<<< orphan*/ *) ; 

mrdb_state*
mrdb_state_get(mrb_state *mrb)
{
  if (!_mrdb_state) {
    _mrdb_state = mrdb_state_new(mrb);
  }
  return _mrdb_state;
}