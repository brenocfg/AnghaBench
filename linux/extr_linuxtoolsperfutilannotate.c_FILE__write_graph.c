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
#define  DARROW_CHAR 131 
#define  LARROW_CHAR 130 
#define  RARROW_CHAR 129 
#define  UARROW_CHAR 128 
 int /*<<< orphan*/  fputs (char const*,void*) ; 

__attribute__((used)) static void FILE__write_graph(void *fp, int graph)
{
	const char *s;
	switch (graph) {

	case DARROW_CHAR: s = "↓"; break;
	case UARROW_CHAR: s = "↑"; break;
	case LARROW_CHAR: s = "←"; break;
	case RARROW_CHAR: s = "→"; break;
	default:		s = "?"; break;
	}

	fputs(s, fp);
}