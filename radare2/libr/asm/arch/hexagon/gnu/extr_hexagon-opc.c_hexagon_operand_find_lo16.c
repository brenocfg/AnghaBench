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
typedef  int /*<<< orphan*/  hexagon_operand ;

/* Variables and functions */
 int /*<<< orphan*/  const* hexagon_operand_find_xx16 (int /*<<< orphan*/  const*,char*) ; 

const hexagon_operand *
hexagon_operand_find_lo16
(const hexagon_operand *operand)
{
  return hexagon_operand_find_xx16 (operand, "_lo16");
}