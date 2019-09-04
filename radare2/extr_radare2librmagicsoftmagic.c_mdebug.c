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
typedef  int /*<<< orphan*/  ut32 ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_showstr (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void mdebug(ut32 offset, const char *str, size_t len) {
	eprintf ("mget @%d: ", offset);
	file_showstr (stderr, str, len);
	(void) fputc('\n', stderr);
	(void) fputc('\n', stderr);
}