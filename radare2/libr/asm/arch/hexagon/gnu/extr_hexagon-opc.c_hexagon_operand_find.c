#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* fmt; } ;
typedef  TYPE_1__ hexagon_operand ;

/* Variables and functions */
 char* alloca (scalar_t__) ; 
 size_t hexagon_operand_count ; 
 TYPE_1__ const* hexagon_operands ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

const hexagon_operand *
hexagon_operand_find
(const hexagon_operand *operand, const char *suffix)
{
  size_t i;
  char *buf;

  buf = alloca (strlen (operand->fmt) + strlen (suffix) + 1);
  strcpy (buf, operand->fmt);
  strcat (buf, suffix);

  for (i = 0; i < hexagon_operand_count; i++)
    if (!strcmp (hexagon_operands [i].fmt, buf))
      return (hexagon_operands + i);

  return NULL;
}