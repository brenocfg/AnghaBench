#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int attlen; scalar_t__ attbyval; } ;
typedef  TYPE_1__ SpGistTypeDesc ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 unsigned int MAXALIGN (unsigned int) ; 
 unsigned int VARSIZE_ANY (int /*<<< orphan*/ ) ; 

unsigned int
SpGistGetTypeSize(SpGistTypeDesc *att, Datum datum)
{
	unsigned int size;

	if (att->attbyval)
		size = sizeof(Datum);
	else if (att->attlen > 0)
		size = att->attlen;
	else
		size = VARSIZE_ANY(datum);

	return MAXALIGN(size);
}