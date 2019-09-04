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
struct CodaFid {int* opaque; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 

char * coda_f2s(struct CodaFid *f)
{
	static char s[60];

 	sprintf(s, "(%08x.%08x.%08x.%08x)", f->opaque[0], f->opaque[1], f->opaque[2], f->opaque[3]);

	return s;
}