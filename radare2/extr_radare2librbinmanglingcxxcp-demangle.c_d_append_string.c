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
struct d_print_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_append_buffer (struct d_print_info*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline void
d_append_string (struct d_print_info *dpi, const char *s)
{
  d_append_buffer (dpi, s, strlen (s));
}