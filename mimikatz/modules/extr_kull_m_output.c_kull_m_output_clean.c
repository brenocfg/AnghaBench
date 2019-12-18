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
 int /*<<< orphan*/  SetConsoleOutputCP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  previousConsoleOutput ; 
 int /*<<< orphan*/  previousStdErr ; 
 int /*<<< orphan*/  previousStdOut ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void kull_m_output_clean()
{
#if !defined(_POWERKATZ)
#if !defined(_WINDLL)
	_setmode(_fileno(stdout), previousStdOut);
	_setmode(_fileno(stderr), previousStdErr);
#endif
	SetConsoleOutputCP(previousConsoleOutput);
#endif
}