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
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  GetConsoleOutputCP () ; 
 int /*<<< orphan*/  SetConsoleOutputCP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _O_U8TEXT ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 void* _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  previousConsoleOutput ; 
 void* previousStdErr ; 
 void* previousStdOut ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void kull_m_output_init()
{
#if !defined(_POWERKATZ)
#if !defined(_WINDLL)
	previousStdOut = _setmode(_fileno(stdout), _O_U8TEXT);
	previousStdErr = _setmode(_fileno(stderr), _O_U8TEXT);
#endif
	previousConsoleOutput = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
#endif
}