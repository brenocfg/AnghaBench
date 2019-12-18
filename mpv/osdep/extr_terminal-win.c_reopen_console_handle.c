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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freopen (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_a_console (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reopen_console_handle(DWORD std, int fd, FILE *stream)
{
    if (is_a_console(GetStdHandle(std))) {
        freopen("CONOUT$", "wt", stream);
        dup2(fileno(stream), fd);
        setvbuf(stream, NULL, _IONBF, 0);
    }
}