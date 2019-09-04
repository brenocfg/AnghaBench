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
struct vsnprintf_closure {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_char (char const,struct vsnprintf_closure*) ; 

__attribute__((used)) static void
write_fill (const char ch, int n, struct vsnprintf_closure *cc)
{
  int i;
  for (i = 0; i < n; i++)
    write_char (ch, cc);
}