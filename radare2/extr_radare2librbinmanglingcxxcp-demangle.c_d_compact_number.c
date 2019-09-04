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
struct d_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 int d_number (struct d_info*) ; 
 char d_peek_char (struct d_info*) ; 

__attribute__((used)) static int
d_compact_number (struct d_info *di)
{
  int num;
  if (d_peek_char (di) == '_')
    num = 0;
  else if (d_peek_char (di) == 'n')
    return -1;
  else
    num = d_number (di) + 1;

  if (num < 0 || ! d_check_char (di, '_'))
    return -1;
  return num;
}