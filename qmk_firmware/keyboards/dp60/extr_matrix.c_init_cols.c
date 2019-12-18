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

/* Variables and functions */
 int /*<<< orphan*/  D2 ; 
 int /*<<< orphan*/  D3 ; 
 int /*<<< orphan*/  D5 ; 
 int /*<<< orphan*/  D6 ; 
 int /*<<< orphan*/  F0 ; 
 int /*<<< orphan*/  F1 ; 
 int /*<<< orphan*/  F4 ; 
 int /*<<< orphan*/  F5 ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unselect_cols () ; 

__attribute__((used)) static void init_cols(void)
{
  setPinOutput(F0);
  setPinOutput(F1);
  setPinOutput(F4);
  setPinOutput(F5);

  setPinOutput(D2);
  setPinOutput(D3);
  setPinOutput(D5);
  setPinOutput(D6);

  unselect_cols();
}