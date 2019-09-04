#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ hexagon_operand ;

/* Variables and functions */
 size_t hexagon_operand_count ; 
 TYPE_1__ const* hexagon_operands ; 
 size_t strcspn (char const*,char*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

const hexagon_operand *
hexagon_lookup_operand
(const char *name)
{
  size_t op_len, fm_len;
  size_t i;

  /* Get the length of the operand syntax up to a separator. */
  op_len = strcspn (name, " .,");

  for (i = 0; i < hexagon_operand_count; i++)
    {
      fm_len = strlen  (hexagon_operands [i].fmt);

      if (op_len == fm_len && !strncmp (name, hexagon_operands [i].fmt, op_len))
        return (hexagon_operands + i);
    }

  return NULL;
}