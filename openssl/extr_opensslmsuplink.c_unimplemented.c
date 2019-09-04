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
typedef  int /*<<< orphan*/  TCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  OPENSSL_showfatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TerminateProcess (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg ; 

__attribute__((used)) static void unimplemented(void)
{
    OPENSSL_showfatal(sizeof(TCHAR) == sizeof(char) ? "%s\n" : "%S\n", msg);
    TerminateProcess(GetCurrentProcess(), 1);
}