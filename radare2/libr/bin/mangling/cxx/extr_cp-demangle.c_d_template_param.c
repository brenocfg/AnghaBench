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
struct demangle_component {int dummy; } ;
struct d_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 int d_compact_number (struct d_info*) ; 
 struct demangle_component* d_make_template_param (struct d_info*,int) ; 

__attribute__((used)) static struct demangle_component *
d_template_param (struct d_info *di)
{
  int param;

  if (! d_check_char (di, 'T'))
    return NULL;

  param = d_compact_number (di);
  if (param < 0)
    return NULL;

  return d_make_template_param (di, param);
}