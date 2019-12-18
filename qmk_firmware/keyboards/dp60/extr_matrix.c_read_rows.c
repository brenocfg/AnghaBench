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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  B7 ; 
 int /*<<< orphan*/  D4 ; 
 int /*<<< orphan*/  E6 ; 
 int /*<<< orphan*/  F6 ; 
 int /*<<< orphan*/  F7 ; 
 scalar_t__ readPin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t read_rows()
{
  return ((readPin(E6) ? 0 : (1 << 0)) |
          (readPin(F6) ? 0 : (1 << 1)) |
          (readPin(F7) ? 0 : (1 << 2)) |
          (readPin(B7) ? 0 : (1 << 3)) |
          (readPin(D4) ? 0 : (1 << 4)));
}