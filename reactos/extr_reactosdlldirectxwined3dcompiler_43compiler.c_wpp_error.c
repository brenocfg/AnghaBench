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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  wpp_write_message (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpp_write_message_var (char*,...) ; 

__attribute__((used)) static void wpp_error(const char *file, int line, int col, const char *_near,
                      const char *msg, va_list ap)
{
    wpp_write_message_var("%s:%d:%d: %s: ", file ? file : "'main file'",
                          line, col, "Error");
    wpp_write_message(msg, ap);
    wpp_write_message_var("\n");
}