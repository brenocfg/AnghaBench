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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
dup_arg_item(mrb_state *mrb, const char *item)
{
  size_t buflen = strlen(item) + 1;
  char *buf = (char*)mrb_malloc(mrb, buflen);
  memcpy(buf, item, buflen);
  return buf;
}