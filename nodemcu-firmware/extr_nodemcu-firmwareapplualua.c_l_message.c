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

/* Variables and functions */
 int /*<<< orphan*/  luai_writestringerror (char*,char const*) ; 

__attribute__((used)) static void l_message (const char *pname, const char *msg) {
#if defined(LUA_USE_STDIO)
  if (pname) c_fprintf(c_stderr, "%s: ", pname);
  c_fprintf(c_stderr, "%s\n", msg);
  c_fflush(c_stderr);
#else
  if (pname) luai_writestringerror("%s: ", pname);
  luai_writestringerror("%s\n", msg);
#endif
}