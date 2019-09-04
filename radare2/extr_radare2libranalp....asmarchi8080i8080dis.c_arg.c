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
struct arg_t {int type; int const shift; int const mask; int /*<<< orphan*/ * fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arg(char* s, int const cmd, struct arg_t const* arg, int val) {
  if (arg->type == 3) {
    strcat(s, arg->fmt[(cmd >> arg->shift) & arg->mask]);
  } else {
    if (arg->type == 1)
      sprintf(s, "%02X", val & 0xff);
    else if (arg->type == 2)
      sprintf(s, "%04X", val);
  }
}