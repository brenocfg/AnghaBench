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
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unselect_cols(void)
{
  writePinHigh(F0);
  writePinHigh(F1);
  writePinHigh(F4);
  writePinHigh(F5);

  writePinHigh(D2);
  writePinHigh(D3);
  writePinHigh(D5);
  writePinHigh(D6);
}